#pragma once
#include "PriceLevel.h"
#include "PriceLevelPool.hpp"
#include <map>
#include <unordered_map>

class OrderBook {
public:
    explicit OrderBook(PriceLevelPool& levels) : levels_(levels) {}
    PriceLevel* level(Price price, bool create);
    void remove_level(Price price, Side side) noexcept;
    std::map<Price, PriceLevel*>& bids() noexcept { return bids_; }
    std::map<Price, PriceLevel*>& asks() noexcept { return asks_; }
    std::unordered_map<OrderId, Order*>& orders() noexcept { return orders_; }
private:
    PriceLevelPool& levels_;
    std::map<Price, PriceLevel*> bids_;
    std::map<Price, PriceLevel*> asks_;
    std::unordered_map<OrderId, Order*> orders_;
};
