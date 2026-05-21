#include "monitor_engine.hpp"

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
    return SystemSnapshot();
}
