//
// Created by User on 2/17/2026.
//

#ifndef NOVA_TradingTypes_H
#define NOVA_TradingTypes_H

#include <stdint.h>

/* Constant definitions */
static constexpr uint32_t MAX_SYMBOL_LEN = 50;

/* Error Codes*/
enum class ErrorCode: uint16_t {
    OK = 0,
    INVALID_PRICE = 1,
    INSUFFICIENT_QTY = 2,
    NETWORK_ERROR = 3,
};

enum class Side : uint8_t {
    BUY = 1,
    SELL = 2
};

enum class Type : uint8_t {
    Limit = 1,
    Market = 2
};

typedef uint64_t Price; 

struct Order {
    uint64_t timestamp;
    uint64_t symbolID;

    Price price;
    uint32_t orderID;
    uint16_t quantity;

    Side side;
    Type type;
    uint8_t reserved[4];
};

struct Trade {
    uint64_t matchID;
    uint64_t timestamp;

    Price price;
    uint32_t tradeID;
    uint16_t executedQty;

    Side AggressorSide;
    uint8_t reserved[5]; // Manually padding to hit 32 bytes
};

#endif // NOVA_TradingTypes_H
