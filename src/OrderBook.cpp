#include "OrderBook.h"

PriceLevel* OrderBook::level(Price price, bool create) {
    auto it = bids_.find(price);
    if (it != bids_.end() || !create) return it == bids_.end() ? nullptr : it->second;
    auto* created = levels_.acquire();
    if (!created) return nullptr;
    created->price = price; bids_.emplace(price, created); return created;
}
void OrderBook::remove_level(Price price, Side side) noexcept {
    auto& levels = side == Side::Buy ? bids_ : asks_;
    auto it = levels.find(price); if (it != levels.end()) { levels_.release(it->second); levels.erase(it); }
}
