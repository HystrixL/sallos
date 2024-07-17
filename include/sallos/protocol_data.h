#pragma once

#include <type_traits>

template <typename T>
concept ProtocolData =
    std::is_trivial_v<T> && std::is_standard_layout_v<T> && std::is_same_v<typeof(T::CMD_ID), const unsigned short>;
