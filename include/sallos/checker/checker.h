#pragma once

#include <array>
#include <cstddef>
#include <type_traits>

namespace sallos {
template <typename T>
concept AsChecker =
    requires(T t, const std::array<std::byte, 0>& data, const std::array<std::byte, T::kCheckLen>& check) {
        requires std::is_same_v<typeof(T::kCheckLen), const std::size_t>;

        { t.Encode(data) } -> std::same_as<std::array<std::byte, T::kCheckLen>>;

        { t.Verify(data, check) } -> std::same_as<bool>;
    };
}