#ifndef MATCHER_H
#define MATCHER_H

#include <TradingTypes.h>
#include <OrderPool.cpp>
#include <OrderBook.h>

class Matcher { 
Private: 
  std::unordered_map<uint64_t, OrderBook> assetMap;
  // We also need a way to seperate orders based on SymbolID. Hashmap for SymbolID? And then an array for buy vs sell
  // Need anorderbook class to contai both Buy and Sell PriceLevels
  // Then seperate them into buy and sell. 
  // We need to contain both the buy and sell orders
  //
  // HASHMAP of SYMBOLID and ORDERBOOK. 
  // Each OrderBOOK should have Buy and Sell.
  // Within Buy and Sell each should a layered data Sturcutre
  //  Hashmap of Price to PriceLevels* for Updates.
  //  A sorted Container of the Prices to find the Best Prices for Best Bid and offer
  //  Implement an Attemtp a Balanaced BST because with the former approach, I get the sense we might use way more memory
  //
  // PriceLevelPool - So we can create a new PriceLevel if there isn't one. 
  //
  //  
  //
  // We need to Add a GateWay Class to that Calls ROderPool to ge
Public:
  Matcher();
  void processOrder(Order *);
}



#endif
