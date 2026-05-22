#pragma once

#include "process_info/process_info.hpp"

#include <unordered_map>
#include <vector>

class ProcessCollector {
    // pid : snapshot
    std::unordered_map<pid_t, ProcessSnapshot> previous_;
    uint64_t previous_total_cpu_ticks_ = 0;
    
public:
    std::vector<ProcessInfo> collect();

private:
    // TODO: std::optional<ProcessSnapshot>
    ProcessSnapshot readProc(pid_t pid);

    std::vector<pid_t> enumeratePids();

    uid_t readUid(pid_t pid);
    std::string uidToUsername(uid_t uid);

    ProcessInfo snapshotToInfo(
        const ProcessSnapshot& current,
        const ProcessSnapshot* previous,
        uint64_t current_total_cpu_ticks
    );

    uint64_t readTotalCpuTicks(); 

    // TODO: replace hz
    float calculateCpuUsage(
        const ProcessSnapshot& current,
        const ProcessSnapshot* previous
    );

    ProcessSnapshot parseProcLine(const std::string& info_line);
    void parseRestLine(
        const std::string& info_line, 
        std::size_t start_pos, 
        ProcessSnapshot& snapshot
    );
};