//
// Created by User on 2/17/2026.
//

#include "OrderPool.h"

::OrderPool::OrderPool(size_t capacity) {
    pool.reserve(capacity);
}

void ::OrderPool::reset() {
    nextAvailableIndex = 0;
}
