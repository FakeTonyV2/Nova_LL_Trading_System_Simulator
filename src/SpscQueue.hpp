#pragma once
#include <array>
#include <atomic>
#include <cstddef>

template <typename T, std::size_t Capacity>
class SpscQueue {
    static_assert(Capacity > 1);
public:
    bool try_push(const T& value) noexcept {
        const auto head = head_.load(std::memory_order_relaxed);
        const auto next = (head + 1) % Capacity;
        if (next == tail_.load(std::memory_order_acquire)) return false;
        buffer_[head] = value; head_.store(next, std::memory_order_release); return true;
    }
    bool try_pop(T& value) noexcept {
        const auto tail = tail_.load(std::memory_order_relaxed);
        if (tail == head_.load(std::memory_order_acquire)) return false;
        value = buffer_[tail]; tail_.store((tail + 1) % Capacity, std::memory_order_release); return true;
    }
    bool empty() const noexcept { return head_.load() == tail_.load(); }
private:
    alignas(64) std::atomic<std::size_t> head_{0};
    alignas(64) std::atomic<std::size_t> tail_{0};
    std::array<T, Capacity> buffer_{};
};
