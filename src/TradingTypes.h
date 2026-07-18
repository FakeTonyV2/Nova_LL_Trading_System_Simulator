#pragma once

#include <cstdint>
#include <type_traits>

template <typename E>
constexpr auto to_uint(E value) noexcept {
    static_assert(std::is_enum_v<E>, "to_uint requires an enum type");
    return static_cast<std::underlying_type_t<E>>(value);
}

using Price = std::uint64_t; // fixed-point ticks, never floating point in the engine
using Quantity = std::uint32_t;
using SymbolId = std::uint32_t;
using OrderId = std::uint64_t;

enum class Side : std::uint8_t { Buy = 1, Sell = 2 };
enum class OrderType : std::uint8_t { Limit = 1, Market = 2 };
enum class MDType : std::uint8_t { Add = 1, Cancel = 2, Execute = 3, Delete = 4 };

struct Order {
    OrderId id{};
    SymbolId symbol{};
    Price price{};
    Quantity quantity{};
    Quantity remaining{};
    std::uint64_t timestamp_ns{};
    Side side{Side::Buy};
    OrderType type{OrderType::Limit};
    Order* prev{};
    Order* next{};
    bool active{false};
};

struct MDEvent {
    MDType type{MDType::Add};
    std::uint64_t timestamp_ns{};
    SymbolId symbol{};
    OrderId order_id{};
    Price price{};
    Quantity size{};
    Side side{Side::Buy};
    OrderType order_type{OrderType::Limit};
};

struct FillEvent {
    std::uint64_t match_id{};
    std::uint64_t timestamp_ns{};
    OrderId maker_order_id{};
    OrderId taker_order_id{};
    SymbolId symbol{};
    Price price{};
    Quantity quantity{};
    Side aggressor_side{Side::Buy};
};
