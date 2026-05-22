#include "system_monitor.hpp"
#include <chrono>

namespace ch = std::chrono;

SystemSnapshot SystemMonitor::collect() {
    auto cpu = cpu_collector_.collect();
    auto mem = memory_collector_.collect();
    auto proc = process_collector_.collect();
    
    return makeSystemSnapshot(cpu, mem, proc);
}

SystemSnapshot SystemMonitor::makeSystemSnapshot(
    CpuUsage cpu, 
    MemoryInfo mem, 
    std::vector<ProcessInfo> processes
) {
    const auto now = ch::system_clock::now();
    auto timestamp = ch::duration_cast<ch::seconds>(now.time_since_epoch()).count();
    return SystemSnapshot{
        timestamp, cpu, mem, processes
    };
}
