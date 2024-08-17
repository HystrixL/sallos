#pragma once

#include <cstddef>
#include <type_traits>
#include "sallos/utils/plain_continuous.h"

namespace sallos {
template <typename T>
concept AsProtocolData = requires {
    requires PlainContinuous<T>;
    requires std::is_same_v<typeof(T::CMD_ID), const std::byte>;
};
}  // namespace sallos
