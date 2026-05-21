#pragma once
#include <unordered_map>
#include <string>
#include <cstdint>
#include <unistd.h>
#include <sys/types.h>
#include <algorithm>

#include "collectors/structs.hpp"

enum class ProcessState {
    D = 0, // uninterruptible sleep
    R, // running
    S, // sleeping
    T, // traced or stopped
    Z, // zombie
    Unknown
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

/**
 * @brief Класс доменной области, описывающий состояние процесса в системе
 * DTO object
 * @details Смотреть man proc
 */
struct ProcessInfo {
    pid_t pid;
    
    std::string user; // Task's owner

    int64_t priority; // Process priority
    int64_t nice; // 'Nice value' (<0 - higher priority, >0 - lower priority, 0 - not adjusted)
    int virt; // Virtual memory usage
    int res; // How much physical RAM the process is using (kb)
    int shr;

    ProcessState state;
    CpuUsage cpu_usage; 
    MemoryInfo mem_usage;

    uint64_t cpu_ticks; // Time/time+ in top
    std::string command;

    friend std::ostream& operator<<(std::ostream& os, const ProcessInfo& info);
 
    void clear();
};

/**
 * @brief Сырое представление данных о процессе в момент времени 
 */
struct ProcessSnapshot {
    pid_t pid;
        
    uid_t uid;
    std::string command;
    char state;

    //proc/[pid]/stat

    int64_t priority;
    int64_t nice;

    uint64_t utime; // user mode ticks
    uint64_t stime; // kernel mode ticks
    uint64_t starttime; // ticks since boot

    uint64_t virt_size;
    int64_t rss_pages; // Resident Set Size: number of pages the process has in real memory
    int64_t shared_pages;
    
    uint64_t cpu_ticks;
};


static std::string format_cpu_time(uint64_t ticks);

