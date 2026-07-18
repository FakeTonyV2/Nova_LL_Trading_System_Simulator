#pragma once
#include "SpscQueue.hpp"
#include <cstdint>
#include <fstream>
#include <string>

struct LogEvent { std::uint64_t timestamp_ns{}; std::uint32_t code{}; std::uint64_t value{}; };
class AsyncLogger {
public:
    explicit AsyncLogger(const std::string& path) : output_(path) {}
    bool try_log(LogEvent event) noexcept { return queue_.try_push(event); }
    std::size_t drain() { LogEvent event{}; std::size_t count=0; while(queue_.try_pop(event)){ output_<<event.timestamp_ns<<','<<event.code<<','<<event.value<<'\n'; ++count; } output_.flush(); return count; }
private:
    SpscQueue<LogEvent, 65536> queue_;
    std::ofstream output_;
};
