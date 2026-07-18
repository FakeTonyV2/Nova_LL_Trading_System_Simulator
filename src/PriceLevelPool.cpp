#include "PriceLevelPool.hpp"

PriceLevelPool::PriceLevelPool(std::size_t capacity) : storage_(capacity), free_() {
    free_.reserve(capacity);
    for (std::size_t i = 0; i < capacity; ++i) free_.push_back(capacity - i - 1);
}
PriceLevel* PriceLevelPool::acquire() noexcept {
    if (free_.empty()) return nullptr;
    auto* level = &storage_[free_.back()]; free_.pop_back(); *level = {}; level->active = true; return level;
}
void PriceLevelPool::release(PriceLevel* level) noexcept {
    if (!level || level < storage_.data() || level >= storage_.data() + storage_.size()) return;
    level->active = false; free_.push_back(static_cast<std::size_t>(level - storage_.data()));
}
void PriceLevelPool::reset() noexcept { free_.clear(); for (std::size_t i=0;i<storage_.size();++i) free_.push_back(storage_.size()-i-1); }
