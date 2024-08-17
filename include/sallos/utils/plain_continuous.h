#pragma once

#include <type_traits>

namespace sallos {
template <typename T>
concept PlainContinuous = requires {
    requires std::is_trivial_v<T>;
    requires std::is_standard_layout_v<T>;
    requires std::alignment_of_v<T> == 1;
};
}