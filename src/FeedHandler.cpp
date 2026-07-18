#include "FeedHandler.hpp"
#include <fstream>
#include <sstream>
#include <vector>

std::size_t FeedHandler::replay_file(const std::string& path) {
    std::ifstream input(path); if (!input) return 0; std::string line; std::size_t count=0;
    while (std::getline(input,line)) {
        if (line.empty() || line[0]=='#') continue;
        std::stringstream ss(line); std::string field; std::vector<std::string> fields;
        while (std::getline(ss,field,',')) fields.push_back(field);
        if (fields.size() < 5) continue;
        try { MDEvent e{}; e.timestamp_ns=std::stoull(fields[0]); e.type=static_cast<MDType>(std::stoi(fields[1])); e.order_id=std::stoull(fields[2]); e.price=std::stoull(fields[3]); e.size=static_cast<Quantity>(std::stoul(fields[4])); e.side=static_cast<Side>(fields.size()>5?std::stoi(fields[5]):1); if(output_.try_push(e)) ++count; else break; } catch (...) { continue; }
    }
    return count;
}
