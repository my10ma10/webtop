#pragma once
#include <unordered_map>
#include <string>
#include <unistd.h>
#include <sys/types.h>

enum class ProcessState {
    D = 0, // uninterruptible sleep
    R, // running
    S, // sleeping
    T, // traced or stopped
    Z, // zombie
};

inline std::unordered_map<char, ProcessState> char_to_state = {
    {'D', ProcessState::D},
    {'R', ProcessState::R},
    {'S', ProcessState::S},
    {'T', ProcessState::T},
    {'Z', ProcessState::Z}
};


inline std::unordered_map<ProcessState, char> state_to_char = {
    {ProcessState::D, 'D'},
    {ProcessState::R, 'R'},
    {ProcessState::S, 'S'},
    {ProcessState::T, 'T'},
    {ProcessState::Z, 'Z'}
};

struct ProcessInfo {
    pid_t pid; // Process id
    std::string user; // Task's owner
    int pr; // Process priority
    int ni; // 'Nice value' (<0 - higher priority, >0 - lower priority, 0 - not adjusted)
    int virt; // Virtual memory usage
    int res; // How much physical RAM the process is using (kb)
    int shr; // Shared memory size (kb)
    ProcessState state;
    float cpu_percent; 
    float mem_persent;
    struct timeval time_plus;
    std::string command;

    ProcessInfo() = default;
    
    ProcessInfo(const ProcessInfo&) = default;
    ProcessInfo& operator=(const ProcessInfo&) = default;
    ProcessInfo(ProcessInfo&&) = default;
    ProcessInfo& operator=(ProcessInfo&&) = default;

    friend std::ostream& operator<<(std::ostream& os, const ProcessInfo& info);
 
    void clear();
};
