#include <sallos/diabase/diabase.h>
#include <array>
#include <cstddef>
#include <iostream>
#include "sallos/checker/checksum.h"
#include "sallos/protocol/frame.h"
#include "sallos/utils/sequence_factory.h"

using namespace sallos;

struct FakePort {
    inline constexpr static std::size_t BUFFER_SIZE = 64;
    std::array<std::byte, BUFFER_SIZE> cache{};

    void Send(const std::array<std::byte, BUFFER_SIZE>& buffer) { cache = buffer; }

    [[nodiscard]] std::array<std::byte, BUFFER_SIZE> Recv() const { return cache; }
};

enum class State { A, B, C, D };

PROTOCOL GimbalInfo {
    inline constexpr static std::byte CMD_ID{0x15};
    double yaw, roll, pitch;
    bool is_enable;
    int target;
    State state;
};

PROTOCOL ChassisInfo {
    inline constexpr static std::byte CMD_ID{0x20};
    double yaw, roll, pitch;
    bool is_enable;
    int target;
    State state;
};

static_assert(AsCommunicator<FakePort>, "FakePort must AsCommunicator.");

static_assert(AsProtocolData<GimbalInfo>, "Gimbal must AsProtocolData.");

int main() {
    FakePort fake_port{};
    CheckSum check_sum{};
    GimbalInfo gi{
        .yaw = 123.456, .roll = 234.567, .pitch = 345.678, .is_enable = true, .target = 114514, .state = State::C};

    std::cout << "=================================================\n";

    for (auto i = 0; i < 10; ++i) {
        sallos::Send(fake_port, gi, check_sum);

        auto ret = sallos::Recv<GimbalInfo>(fake_port, check_sum);

        if (ret.has_value()) {
            std::cout << ret->yaw << "  " << ret->roll << "  " << ret->pitch << "  " << ret->target << "  "
                      << static_cast<unsigned>(ret->state) << std::endl;
        } else {
            switch (ret.error()) {
                case BiotiteResult::SUCCESS:
                    std::cout << "SUCCESS" << std::endl;
                    break;
                case BiotiteResult::UNEXPECTED_HEAD:
                    std::cout << "UNEXPECTED_HEAD" << std::endl;
                    break;
                case BiotiteResult::UNEXPECTED_LEN:
                    std::cout << "UNEXPECTED_LEN" << std::endl;
                    break;
                case BiotiteResult::UNEXPECTED_CHECK:
                    std::cout << "UNEXPECTED_CHECK" << std::endl;
                    break;
                case BiotiteResult::UNEXPECTED_CMD:
                    std::cout << "UNEXPECTED_CMD" << std::endl;
                    break;
            }
        }

        switch (GetSeqState()) {
            case SequenceState::kNormal:
                std::cout << "kNormal" << std::endl;
                break;
            case SequenceState::kInversed:
                std::cout << "kInversed" << std::endl;
                break;
            case SequenceState::kDropped:
                std::cout << "kDropped" << std::endl;
                break;
            case SequenceState::kRepeat:
                std::cout << "kRepeat" << std::endl;
                break;
        }

        gi.yaw *= 2;
        gi.roll *= 3;
        gi.pitch *= 4;
        gi.is_enable = !gi.is_enable;
        ++gi.target;
    }

    std::cout << "=================================================\n";

    sallos::Send(fake_port, gi, check_sum);
    fake_port.cache[0] = std::byte{0x27};
    auto ret = sallos::Recv<ChassisInfo>(fake_port, check_sum);
    if (ret.has_value()) {
        std::cout << ret->yaw << "  " << ret->roll << "  " << ret->pitch << "  " << ret->target << "  "
                  << static_cast<unsigned>(ret->state) << std::endl;
    } else {
        switch (ret.error()) {
            case BiotiteResult::SUCCESS:
                std::cout << "SUCCESS" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_HEAD:
                std::cout << "UNEXPECTED_HEAD" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_LEN:
                std::cout << "UNEXPECTED_LEN" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_CHECK:
                std::cout << "UNEXPECTED_CHECK" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_CMD:
                std::cout << "UNEXPECTED_CMD" << std::endl;
                break;
        }
    }

    sallos::Send(fake_port, gi, check_sum);
    fake_port.cache[1] = std::byte{0x27};
    ret = sallos::Recv<ChassisInfo>(fake_port, check_sum);
    if (ret.has_value()) {
        std::cout << ret->yaw << "  " << ret->roll << "  " << ret->pitch << "  " << ret->target << "  "
                  << static_cast<unsigned>(ret->state) << std::endl;
    } else {
        switch (ret.error()) {
            case BiotiteResult::SUCCESS:
                std::cout << "SUCCESS" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_HEAD:
                std::cout << "UNEXPECTED_HEAD" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_LEN:
                std::cout << "UNEXPECTED_LEN" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_CHECK:
                std::cout << "UNEXPECTED_CHECK" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_CMD:
                std::cout << "UNEXPECTED_CMD" << std::endl;
                break;
        }
    }

    sallos::Send(fake_port, gi, check_sum);
    fake_port.cache[3] = std::byte{0x27};
    ret = sallos::Recv<ChassisInfo>(fake_port, check_sum);
    if (ret.has_value()) {
        std::cout << ret->yaw << "  " << ret->roll << "  " << ret->pitch << "  " << ret->target << "  "
                  << static_cast<unsigned>(ret->state) << std::endl;
    } else {
        switch (ret.error()) {
            case BiotiteResult::SUCCESS:
                std::cout << "SUCCESS" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_HEAD:
                std::cout << "UNEXPECTED_HEAD" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_LEN:
                std::cout << "UNEXPECTED_LEN" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_CHECK:
                std::cout << "UNEXPECTED_CHECK" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_CMD:
                std::cout << "UNEXPECTED_CMD" << std::endl;
                break;
        }
    }
    sallos::Send(fake_port, gi, check_sum);
    ret = sallos::Recv<ChassisInfo>(fake_port, check_sum);
    if (ret.has_value()) {
        std::cout << ret->yaw << "  " << ret->roll << "  " << ret->pitch << "  " << ret->target << "  "
                  << static_cast<unsigned>(ret->state) << std::endl;
    } else {
        switch (ret.error()) {
            case BiotiteResult::SUCCESS:
                std::cout << "SUCCESS" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_HEAD:
                std::cout << "UNEXPECTED_HEAD" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_LEN:
                std::cout << "UNEXPECTED_LEN" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_CHECK:
                std::cout << "UNEXPECTED_CHECK" << std::endl;
                break;
            case BiotiteResult::UNEXPECTED_CMD:
                std::cout << "UNEXPECTED_CMD" << std::endl;
                break;
        }
    }

    std::cout << "=================================================\n";

    sallos::Send(fake_port, gi, check_sum);
    for (auto i = 0; i < 5; ++i) {
        auto ret = sallos::Recv<GimbalInfo>(fake_port, check_sum);
        if (ret.has_value()) {
            std::cout << ret->yaw << "  " << ret->roll << "  " << ret->pitch << "  " << ret->target << "  "
                      << static_cast<unsigned>(ret->state) << std::endl;
        } else {
            switch (ret.error()) {
                case BiotiteResult::SUCCESS:
                    std::cout << "SUCCESS" << std::endl;
                    break;
                case BiotiteResult::UNEXPECTED_HEAD:
                    std::cout << "UNEXPECTED_HEAD" << std::endl;
                    break;
                case BiotiteResult::UNEXPECTED_LEN:
                    std::cout << "UNEXPECTED_LEN" << std::endl;
                    break;
                case BiotiteResult::UNEXPECTED_CHECK:
                    std::cout << "UNEXPECTED_CHECK" << std::endl;
                    break;
                case BiotiteResult::UNEXPECTED_CMD:
                    std::cout << "UNEXPECTED_CMD" << std::endl;
                    break;
            }
        }
        switch (GetSeqState()) {
            case SequenceState::kNormal:
                std::cout << "kNormal" << std::endl;
                break;
            case SequenceState::kInversed:
                std::cout << "kInversed" << std::endl;
                break;
            case SequenceState::kDropped:
                std::cout << "kDropped" << std::endl;
                break;
            case SequenceState::kRepeat:
                std::cout << "kRepeat" << std::endl;
                break;
        }
    }
}