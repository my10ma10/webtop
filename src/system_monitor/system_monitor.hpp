#pragma once
#include <string>
#include <vector>

#include "collectors/cpu_collector.hpp"
#include "collectors/memory_collector.hpp"
#include "collectors/process_collector.hpp"
#include "system_snapshot.hpp"

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
