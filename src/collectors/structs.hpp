#pragma once
#include <vector>
#include <string>
#include <cstdint>

/*
in /proc/stat:
    user nice system idle iowait irq softirq steal guest guest_nice
*/


struct CpuStatSnapshot {
    std::string cpu_name;
    uint64_t user = 0;
    uint64_t nice = 0;
    uint64_t system = 0;
    uint64_t idle = 0;
    uint64_t iowait = 0;
    uint64_t irq = 0;
    uint64_t softirq = 0;
    uint64_t steal = 0;
};

struct CpuCoreUsage {
    float usage_percent = 0.0f;
};

struct CpuUsage {
    float total = 0.0f;
    std::vector<CpuCoreUsage> cores;
};


struct MemoryUsage {
    float usage_persent = 0.0f;
};

struct MemoryInfo {
    uint64_t total_kb = 0;
    uint64_t used_kb = 0;
    uint64_t available_kb = 0;
    uint64_t free_kb = 0;

    MemoryUsage usage;
};
