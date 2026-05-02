//
// Created by User on 2/24/2026.
//

#ifndef NOVA_PRICELEVEL_H
#define NOVA_PRICELEVEL_H

struct PriceLevel {
    double price;
    uint64_t totalVolume;
    uint32_t orderCount;

    Order* head = nullptr;
    Order* tail = nullptr;

};

#endif //NOVA_PRICELEVEL_H