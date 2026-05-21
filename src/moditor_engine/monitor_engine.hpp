#pragma once
#include <string>
#include <vector>

#include "process_info/process_info.hpp"

class ProcMonitor {
    ProcessInfo proc_info_;

public:
    ProcMonitor() = default;

    void updateInfo();

    void readProc(pid_t pid);

private:    
    std::vector<pid_t> iterateProcesses();

    void parseProcLine(const std::string& info_line);
    void parseRestLine(const std::string& info_line, std::size_t start_pos);

};
