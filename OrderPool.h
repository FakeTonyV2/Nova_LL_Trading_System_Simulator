//
// Created by User on 2/17/2026.
//

#ifndef NOVA_ORDERPOOL_H
#define NOVA_ORDERPOOL_H

#include <vector>
#include <iostream>
#include <stack>

#include "TradingTypes.h"


class OrderPool {
private:
    std::vector<Order> pool;
    std::stack<size_t, std::vector<size_t>> freeList;

public:
    explicit OrderPool(size_t capacity) {
        pool.resize(capacity);

        for (int i = 0; i < capacity; i++) {
            freeList.push(i);
        }
    }

    inline Order* acquire() noexcept {
        if (__builtin_expect(!freeList.empty(), 1)) {
            size_t index = freeList.top();
            freeList.pop();
            return &pool[index];
        }
        return nullptr;
    }

    inline void release (Order* order) noexcept {
        size_t index = order - &pool[0];
        freeList.push(index);
    }

    void reset();
};


#endif //NOVA_ORDERPOOL_H