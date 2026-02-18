cmake_minimum_required(VERSION 4.1)
project(Nova)

set(CMAKE_CXX_STANDARD 20)

add_executable(Nova main.cpp
        TradingTypes.h
        OrderPool.cpp
        OrderPool.h)
