#pragma once

#include <array>
#include <cstddef>
#include <cstring>
#include <memory>
#include "sallos/utils/plain_continuous.h"

namespace sallos {
template <PlainContinuous To, PlainContinuous From>
constexpr To BitCast(const From& from) noexcept {
    std::unique_ptr<To> to = std::make_unique<To>();
    ::memcpy(to.get(), &from, std::min(sizeof(To), sizeof(From)));
    return *to;
}

template <std::size_t LEN, PlainContinuous T>
std::array<std::byte, LEN> ToBytes(T&& data) {
    return BitCast<std::array<std::byte, LEN>>(data);
}

template <PlainContinuous T, std::size_t LEN>
T FromBytes(std::array<std::byte, LEN> bytes) {
    return BitCast<T>(bytes);
}
}  // namespace sallos