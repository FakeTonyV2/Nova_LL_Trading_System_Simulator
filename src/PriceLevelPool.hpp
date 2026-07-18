#pragma once
#include "PriceLevel.h"
#include <cstddef>
#include <vector>

class PriceLevelPool {
public:
    explicit PriceLevelPool(std::size_t capacity);
    PriceLevel* acquire() noexcept;
    void release(PriceLevel*) noexcept;
    void reset() noexcept;
    std::size_t in_use() const noexcept { return storage_.size() - free_.size(); }
private:
    std::vector<PriceLevel> storage_;
    std::vector<std::size_t> free_;
};
