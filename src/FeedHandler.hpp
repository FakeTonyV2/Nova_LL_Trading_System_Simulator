#pragma once
#include "SpscQueue.hpp"
#include "TradingTypes.h"
#include <cstddef>
#include <string>

class FeedHandler {
public:
    explicit FeedHandler(SpscQueue<MDEvent, 65536>& output) : output_(output) {}
    std::size_t replay_file(const std::string& path);
private:
    SpscQueue<MDEvent, 65536>& output_;
};
