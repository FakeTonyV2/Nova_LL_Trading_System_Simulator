#include "Matcher.hpp"
#include <cassert>
#include <iostream>

int main() {
    SpscQueue<FillEvent, 65536> fills;
    Matcher matcher(16, 16, fills);
    assert(matcher.process_order({MDType::Add, 1, 7, 1, 100, 10, Side::Sell}));
    assert(matcher.process_order({MDType::Add, 2, 7, 2, 101, 4, Side::Buy}));
    FillEvent fill{}; assert(fills.try_pop(fill)); assert(fill.price == 100 && fill.quantity == 4);
    assert(matcher.process_order({MDType::Cancel, 3, 7, 1, 0, 0, Side::Sell}));
    assert(matcher.orders_in_use() == 0);
    std::cout << "nova_tests: ok\n";
}
