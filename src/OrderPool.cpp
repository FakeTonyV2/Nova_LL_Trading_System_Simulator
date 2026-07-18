#include "OrderPool.h"

OrderPool::OrderPool(std::size_t capacity) : storage_(capacity), free_() {
    free_.reserve(capacity);
    for (std::size_t i = 0; i < capacity; ++i) free_.push_back(capacity - i - 1);
}

Order* OrderPool::acquire() noexcept {
    if (free_.empty()) return nullptr;
    auto* order = &storage_[free_.back()];
    free_.pop_back();
    *order = {};
    order->active = true;
    return order;
}

void OrderPool::release(Order* order) noexcept {
    if (!order || order < storage_.data() || order >= storage_.data() + storage_.size()) return;
    const auto index = static_cast<std::size_t>(order - storage_.data());
    order->active = false;
    free_.push_back(index);
}

void OrderPool::reset() noexcept {
    free_.clear();
    for (std::size_t i = 0; i < storage_.size(); ++i) free_.push_back(storage_.size() - i - 1);
}
