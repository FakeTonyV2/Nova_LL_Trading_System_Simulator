#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "PriceLevel.h"

typedef struct OrderBook_T {
  static constexpr size_t MAX_LEVELS = 8192;
  std::array<PriceLevel, MAX_LEVELS> bid_levels;
  std::array<PriceLevel, MAX_LEVELS> ask_levels;
  uint32_t best_bid_idx = 0;
  uint32_t best_ask_idx = MAX_LEVELS - 1;
} OrderBook;
#endif // !ORDERBOOK_H
