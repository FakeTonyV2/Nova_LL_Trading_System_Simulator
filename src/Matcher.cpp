#include "Matcher.hpp"

Matcher::Matcher(std::size_t order_capacity, std::size_t level_capacity, SpscQueue<FillEvent, 65536>& executions)
    : orders_(order_capacity), levels_(level_capacity), executions_(executions) {}

void Matcher::append(OrderBook& book, PriceLevel* level, Order* order) noexcept {
    order->prev = level->tail; order->next = nullptr;
    if (level->tail) level->tail->next = order; else level->head = order;
    level->tail = order; level->total_quantity += order->remaining; ++level->order_count;
    book.orders()[order->id] = order;
}
void Matcher::unlink(OrderBook& book, PriceLevel* level, Order* order) noexcept {
    if (order->prev) order->prev->next = order->next; else level->head = order->next;
    if (order->next) order->next->prev = order->prev; else level->tail = order->prev;
    level->total_quantity -= order->remaining; --level->order_count; book.orders().erase(order->id); orders_.release(order);
}
bool Matcher::add(const MDEvent& e) noexcept {
    auto [it, inserted] = books_.try_emplace(e.symbol, levels_); auto& book = it->second;
    Order* incoming = orders_.acquire(); if (!incoming) return false;
    incoming->id=e.order_id; incoming->symbol=e.symbol; incoming->price=e.price; incoming->quantity=e.size; incoming->remaining=e.size; incoming->timestamp_ns=e.timestamp_ns; incoming->side=e.side; incoming->type=OrderType::Limit;
    auto& opposite = e.side == Side::Buy ? book.asks() : book.bids();
    auto crosses = [&]() { return !opposite.empty() && (e.side == Side::Buy ? e.price >= opposite.begin()->first : e.price <= opposite.rbegin()->first); };
    while (incoming->remaining && crosses()) {
        auto lit = e.side == Side::Buy ? opposite.begin() : std::prev(opposite.end()); auto* level = lit->second; auto* resting = level->head;
        while (incoming->remaining && resting) {
            auto* next = resting->next; const auto qty = incoming->remaining < resting->remaining ? incoming->remaining : resting->remaining;
            if (!executions_.try_push(FillEvent{next_match_id_++, e.timestamp_ns, resting->id, incoming->id, e.symbol, resting->price, qty, e.side})) { orders_.release(incoming); return false; }
            incoming->remaining -= qty; resting->remaining -= qty; level->total_quantity -= qty;
            if (!resting->remaining) unlink(book, level, resting); else resting = next;
        }
        if (level->order_count == 0) { opposite.erase(lit); levels_.release(level); }
    }
    if (incoming->remaining && e.type != OrderType::Market) {
        auto& own = e.side == Side::Buy ? book.bids() : book.asks(); auto lit = own.find(e.price); PriceLevel* level = nullptr;
        if (lit == own.end()) { level = levels_.acquire(); if (!level) { orders_.release(incoming); return false; } level->price=e.price; own.emplace(e.price, level); } else level=lit->second;
        append(book, level, incoming);
    } else orders_.release(incoming);
    return true;
}
bool Matcher::cancel(OrderId id, SymbolId symbol, Quantity amount) noexcept {
    auto bit = books_.find(symbol); if (bit == books_.end()) return false; auto& book=bit->second; auto it=book.orders().find(id); if(it==book.orders().end()) return false; auto* order=it->second; auto& side=order->side==Side::Buy?book.bids():book.asks(); auto lit=side.find(order->price); auto* level=lit->second; const auto reduction=amount==0||amount>order->remaining?order->remaining:amount; order->remaining-=reduction; level->total_quantity-=reduction; if(!order->remaining){ unlink(book,level,order); if(level->order_count==0){levels_.release(level);side.erase(lit);} } return true;
}
bool Matcher::process_order(const MDEvent& event) noexcept { if (event.type == MDType::Add) return add(event); if (event.type == MDType::Cancel || event.type == MDType::Delete || event.type == MDType::Execute) return cancel(event.order_id,event.symbol,event.size); return true; }
