#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <numeric>

template <std::size_t DATA_LEN, std::size_t CHECK_LEN>
struct Checker {
    typedef std::array<unsigned char, CHECK_LEN> CheckArray;
    using DataArray = std::array<unsigned char, DATA_LEN>;

    virtual CheckArray Encode(DataArray) = 0;

    virtual bool Verify(DataArray data, CheckArray check) { return Encode(data) == check; }
};

template <std::size_t DATA_LEN>
struct CheckSum : public Checker<DATA_LEN, 1> {
    Checker<DATA_LEN, 1>::CheckArray Encode(Checker<DATA_LEN, 1>::DataArray data) final {
        return {std::accumulate(data.begin(), data.end(), 0)};
    }
};