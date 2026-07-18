#pragma once
#include "TradingTypes.h"

struct PriceLevel {
    Price price{};
    Quantity total_quantity{};
    std::uint32_t order_count{};
    Order* head{};
    Order* tail{};
    bool active{false};
};
