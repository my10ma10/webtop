#pragma once
#include <string>
#include <vector>

#include "collectors/structs.hpp"
#include "process_info/process_info.hpp"

#include "collectors/cpu_collector.hpp"
#include "collectors/memory_collector.hpp"
#include "collectors/process_collector.hpp"

struct SystemSnapshot {
    CpuUsage cpu_usage;
    MemoryInfo memory_info;
    std::vector<ProcessInfo> processes;
};

class SystemMonitor {
    CpuCollector cpu_collector_;
    MemoryCollector memory_collector_;
    ProcessCollector process_collector_;

public:
    SystemMonitor() = default;
    
    SystemSnapshot collect();

private: 
    SystemSnapshot makeSystemSnapshot(
        CpuUsage cpu, 
        MemoryInfo mem, 
        std::vector<ProcessInfo> processes
    );
};
