#pragma once

#include <array>
#include <cstddef>

#define __cpp_concepts 202002L

#include "expected"
#include "sallos/checker/checker.h"
#include "sallos/protocol/protocol_data.h"
#include "sallos/utils/bit.h"
#include "sallos/utils/pack_macro.h"
#include "sallos/utils/plain_continuous.h"
#include "sallos/utils/sequence_factory.h"

namespace sallos {
struct ProtocolDefinition {
    static constexpr std::byte Head{0x3e};
    static constexpr std::byte Tail{0xff};
};

enum class BiotiteResult { SUCCESS, UNEXPECTED_HEAD, UNEXPECTED_LEN, UNEXPECTED_CHECK, UNEXPECTED_CMD };

template <AsProtocolData T, AsChecker Checker>
PROTOCOL Frame {
    std::byte head;                                   // 帧头
    unsigned char length;                             // 数据段长度
    unsigned char sequence;                           // 序号
    std::array<std::byte, Checker::kCheckLen> check;  // 校验位
    std::byte cmd_id;                                 // 指令码
    T data;                                           // 数据
};

template <AsProtocolData ProtocolData, AsChecker Checker>
Frame<ProtocolData, Checker> ToFrame(ProtocolData data, Checker checker) {
    static SequenceProducer seq_p{};
    return Frame<ProtocolData, Checker>{.head = ProtocolDefinition::Head,
                                        .length = sizeof(data),
                                        .sequence = static_cast<unsigned char>(seq_p.Produce()),
                                        .check = checker.Encode(BitCast<std::array<std::byte, sizeof(data)>>(data)),
                                        .cmd_id = ProtocolData::CMD_ID,
                                        .data = data};
}

template <AsProtocolData ProtocolData, AsChecker Checker>
BiotiteResult Verify(Frame<ProtocolData, Checker> frame, Checker checker) {
    if (frame.head != ProtocolDefinition::Head)
        return BiotiteResult::UNEXPECTED_HEAD;
    if (frame.length != sizeof(frame.data))
        return BiotiteResult::UNEXPECTED_LEN;
    if (frame.check != checker.Encode(BitCast<std::array<std::byte, sizeof(frame.data)>>(frame.data)))
        return BiotiteResult::UNEXPECTED_CHECK;
    if (frame.cmd_id != ProtocolData::CMD_ID)
        return BiotiteResult::UNEXPECTED_CMD;
    return BiotiteResult::SUCCESS;
}

namespace {
inline SequenceConsumer seq_c{};
}

template <AsProtocolData ProtocolData, AsChecker Checker>
std::expected<ProtocolData, BiotiteResult> FromFrame(Frame<ProtocolData, Checker> frame, Checker checker) {
    if (auto result = Verify(frame, checker); result != BiotiteResult::SUCCESS) {
        return std::unexpected{result};
    }
    seq_c.Consume(frame.sequence);

    return frame.data;
}

SequenceState GetSeqState() {
    return seq_c.GetState();
}
}  // namespace sallos
