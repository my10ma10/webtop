#pragma once
#include <cstdint>
#include <vector>

#include "process_info/process_info.hpp"

struct CpuCoreUsage {
    float usage_percent;
};

struct CpuUsage {
    float total;
    std::vector<CpuCoreUsage> cores;
};

struct MemoryUsage {
    uint64_t total;
    uint64_t used;
};


class ProcMonitor {
    ProcessInfo proc_info_;

public:


    void updateInfo();

    void readProc(pid_t pid);

private:    
    std::vector<pid_t> iterateProcesses();
};