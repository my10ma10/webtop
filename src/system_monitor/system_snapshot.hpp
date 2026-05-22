#pragma once
#include <ctime>

#include "process_info/process_info.hpp"
#include "collectors/structs.hpp"

struct SystemSnapshot {
    std::time_t timestamp;

    CpuUsage cpu_usage;
    MemoryInfo memory_info;
    std::vector<ProcessInfo> processes;
};