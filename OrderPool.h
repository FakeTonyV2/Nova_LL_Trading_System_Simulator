//
// Created by User on 2/17/2026.
//

#ifndef NOVA_ORDERPOOL_H
#define NOVA_ORDERPOOL_H

#include <vector>
#include <iostream>
#include "TradingTypes.h"


class OrderPool {
private:
    std::vector<Order> pool;
    uint32_t nextAvailableIndex = 0;

public:
    explicit OrderPool(size_t capacity);

    inline Order* getNextOrder() {
        if (nextAvailableIndex < pool.size()) {
            return &pool[nextAvailableIndex++];
        }
        return nullptr;
    }

    void reset();
};


#endif //NOVA_ORDERPOOL_H