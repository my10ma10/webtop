#pragma once
#include <cstdint>

/*
in /proc/stat:
    user nice system idle iowait irq softirq steal guest guest_nice
*/

struct CpuStatSnapshot {
    uint64_t user;
    uint64_t nice;
    uint64_t system;
    uint64_t idle;
    uint64_t iowait;
    uint64_t irq;
    uint64_t softirq;
    uint64_t steal;
};