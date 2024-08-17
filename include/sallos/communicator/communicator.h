#pragma once

#include <cstddef>
#include <type_traits>
#include "array"

namespace sallos {
template <typename T>
concept AsCommunicator = requires(T t, const std::array<std::byte, T::BUFFER_SIZE>& send_arr) {
    requires std::is_same_v<typeof(T::BUFFER_SIZE), const std::size_t>;

    {
        t.Recv()
    } -> std::same_as<std::array<std::byte, T::BUFFER_SIZE>>;  // std::array<std::byte, T::BUFFER_SIZE>&
                                                               // T::Recv()

    { t.Send(send_arr) } -> std::same_as<void>;  // void T::Send(const std::array<Byte, T::BUFFER_SIZE>)
};
}
