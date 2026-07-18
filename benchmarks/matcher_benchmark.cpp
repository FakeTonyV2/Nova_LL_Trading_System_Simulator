#include "Matcher.hpp"
#include <chrono>
#include <iostream>

int main() {
    SpscQueue<FillEvent, 65536> fills; Matcher matcher(200000, 10000, fills);
    constexpr std::size_t samples=100000; const auto start=std::chrono::steady_clock::now();
    for(std::size_t i=0;i<samples;++i) matcher.process_order({MDType::Add,i,1,static_cast<OrderId>(i),100,1,Side::Buy});
    const auto ns=std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now()-start).count();
    std::cout << "orders="<<samples<<" mean_ns="<<(static_cast<double>(ns)/samples)<<"\n";
}
