#pragma once

#include <atomic>

namespace sallos {
template <typename T = unsigned long>
class SequenceProducer {
    std::atomic<T> sequence_{};

   public:
    unsigned long Produce() { return ++sequence_; }
};

enum class SequenceState { kNormal, kInversed, kDropped, kRepeat };

template <typename T = unsigned long>
class SequenceConsumer {
   public:
    void Consume(unsigned long input, unsigned long threshold = 5) {
        if (input - sequence_ > 0 && input - sequence_ <= threshold + 1) {
            sequence_ = input;
            state = SequenceState::kNormal;
        } else if (input - sequence_ == 0) {
            state = SequenceState::kRepeat;
        } else if (input - sequence_ < 0) {
            state = SequenceState::kInversed;
        } else if (input - sequence_ > threshold + 1) {
            sequence_ = input;
            state = SequenceState::kDropped;
        }
    }
    [[nodiscard]] SequenceState GetState() const { return state; }

   private:
    std::atomic<T> sequence_{};
    std::atomic<SequenceState> state;
};
}  // namespace sallos