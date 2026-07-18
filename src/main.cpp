#include "FeedHandler.hpp"
#include "Matcher.hpp"
#include <iostream>

int main(int argc, char** argv) {
    SpscQueue<MDEvent, 65536> input; SpscQueue<FillEvent, 65536> executions;
    Matcher matcher(1'000'000, 100'000, executions);
    if (argc > 1) { FeedHandler feed(input); const auto loaded=feed.replay_file(argv[1]); MDEvent e{}; std::size_t processed=0; while(input.try_pop(e)){ matcher.process_order(e); ++processed; } std::cout << "loaded="<<loaded<<" processed="<<processed<<" orders_in_use="<<matcher.orders_in_use()<<"\n"; }
    else std::cout << "nova_replay <lobster.csv>\n";
}
