#pragma once
#include "TradingTypes.h"
#include <cstddef>
#include <vector>

class OrderPool {
public:
    explicit OrderPool(std::size_t capacity);
    Order* acquire() noexcept;
    void release(Order* order) noexcept;
    void reset() noexcept;
    std::size_t capacity() const noexcept { return storage_.size(); }
    std::size_t in_use() const noexcept { return storage_.size() - free_.size(); }
private:
    std::vector<Order> storage_;
    std::vector<std::size_t> free_;
};
