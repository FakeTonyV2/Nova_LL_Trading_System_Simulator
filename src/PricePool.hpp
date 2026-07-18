#pragma once
#include "TradingTypes.h"
#include <cstddef>
#include <vector>

class PricePool {
public:
    explicit PricePool(std::size_t capacity) : storage_(capacity) {}
private:
    std::vector<Price> storage_;
};
