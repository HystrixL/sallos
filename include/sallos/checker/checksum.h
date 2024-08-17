#pragma once

#include <sallos/checker/checker.h>
#include <cstddef>
#include <numeric>

namespace sallos {
struct CheckSum {
    static constexpr std::size_t kCheckLen = 1;

    template <std::size_t DATA_LEN>
    std::array<std::byte, kCheckLen> Encode(const std::array<std::byte, DATA_LEN>& data) {
        return {std::accumulate(data.begin(), data.end(), std::byte{}, [](auto&& a, auto&& b) {
            return static_cast<std::byte>(static_cast<unsigned long>(a) + static_cast<unsigned long>(b));
        })};
    }

    template <std::size_t DATA_LEN>
    bool Verify(const std::array<std::byte, DATA_LEN>& data, const std::array<std::byte, kCheckLen>& check) {
        return Encode(data) == check;
    }
};

static_assert(AsChecker<CheckSum>, "CheckSum class should conform to the concept of AsChecker.");
}  // namespace sallos