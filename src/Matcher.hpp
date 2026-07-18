#pragma once
#include "OrderBook.h"
#include "OrderPool.h"
#include "PriceLevelPool.hpp"
#include "SpscQueue.hpp"
#include "TradingTypes.h"
#include <cstddef>
#include <unordered_map>

class Matcher {
public:
    Matcher(std::size_t order_capacity, std::size_t level_capacity, SpscQueue<FillEvent, 65536>& executions);
    bool process_order(const MDEvent& event) noexcept;
    std::size_t orders_in_use() const noexcept { return orders_.in_use(); }
private:
    bool add(const MDEvent&) noexcept;
    bool cancel(OrderId, SymbolId, Quantity) noexcept;
    void append(OrderBook&, PriceLevel*, Order*) noexcept;
    void unlink(OrderBook&, PriceLevel*, Order*) noexcept;
    OrderPool orders_;
    PriceLevelPool levels_;
    SpscQueue<FillEvent, 65536>& executions_;
    std::unordered_map<SymbolId, OrderBook> books_;
    std::uint64_t next_match_id_{1};
};
