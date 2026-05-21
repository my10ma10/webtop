#include "memory_collector.hpp"
#include <fstream>

MemoryInfo MemoryCollector::collect() {
    auto info_map = parseMemInfo();

    MemoryInfo info;

    info.total_kb = info_map["MemTotal"];
    info.available_kb = info_map["MemAvailable"];
    info.free_kb = info_map["MemFree"];
    
    info.used_kb = info.total_kb - info.available_kb;

    if (info.total_kb) {
        info.usage = 100.0f * static_cast<float>(info.used_kb) 
                        / static_cast<float>(info.total_kb);
    }
    return info;
}

std::unordered_map<std::string, uint64_t> MemoryCollector::parseMemInfo() {
    std::ifstream file("/proc/meminfo");

    std::unordered_map<std::string, uint64_t> map;

    std::string key;
    uint64_t value;
    std::string measure_unit;

    constexpr size_t read_count = 3;

    for (size_t i = 0; i < read_count; ++i) {
        file >> key >> value >> measure_unit;
        key.pop_back(); // pop ':'

        map[key] = value;
    }

    return map;
}
