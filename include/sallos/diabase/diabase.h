#pragma once

#include <sallos/communicator/communicator.h>
#include <sallos/protocol/frame.h>

namespace sallos {
template <AsCommunicator Communicator, AsProtocolData ProtocolData, AsChecker Checker>
void Send(Communicator& communicator, ProtocolData& data, Checker& checker) {
    communicator.Send(ToBytes<Communicator::BUFFER_SIZE>(ToFrame(data, checker)));
}

template <AsProtocolData ProtocolData, AsCommunicator Communicator, AsChecker Checker>
auto Recv(Communicator& communicator, Checker& checker) {
    return FromFrame(FromBytes<Frame<ProtocolData, Checker>>(communicator.Recv()), checker);
}
}  // namespace sallos