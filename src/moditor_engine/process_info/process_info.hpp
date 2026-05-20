#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>
#include <unistd.h>
#include <sys/types.h>
#include <algorithm>

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


enum class ProcessState {
    D = 0, // uninterruptible sleep
    R, // running
    S, // sleeping
    T, // traced or stopped
    Z, // zombie
};

const inline std::unordered_map<char, ProcessState> char_to_state = {
    {'D', ProcessState::D},
    {'R', ProcessState::R},
    {'S', ProcessState::S},
    {'T', ProcessState::T},
    {'Z', ProcessState::Z}
};


const inline std::unordered_map<ProcessState, char> state_to_char = {
    {ProcessState::D, 'D'},
    {ProcessState::R, 'R'},
    {ProcessState::S, 'S'},
    {ProcessState::T, 'T'},
    {ProcessState::Z, 'Z'}
};

struct ProcessInfo {
    pid_t pid; // Process id
    std::string user; // Task's owner
    uint64_t priority; // Process priority
    uint64_t nice; // 'Nice value' (<0 - higher priority, >0 - lower priority, 0 - not adjusted)
    int virt; // Virtual memory usage
    int res; // How much physical RAM the process is using (kb)
    int shr; // Shared memory size (kb)
    ProcessState state;
    CpuUsage cpu_usage; 
    MemoryUsage mem_usage;
    uint64_t cpu_ticks; // Time/time+ in top
    std::string command;


    ProcessInfo() = default;
    
    ProcessInfo(const ProcessInfo&) = default;
    ProcessInfo& operator=(const ProcessInfo&) = default;
    ProcessInfo(ProcessInfo&&) = default;
    ProcessInfo& operator=(ProcessInfo&&) = default;

    friend std::ostream& operator<<(std::ostream& os, const ProcessInfo& info);
 
    void clear();
};

static std::string format_cpu_time(uint64_t ticks);

