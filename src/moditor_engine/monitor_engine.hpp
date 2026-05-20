#pragma once
#include <string>

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

    template <typename Stream>
    void skip_fields(Stream& stream, size_t count);

    template <typename T, typename Stream>
    T read_from_stream(Stream& stream);
};

template <typename Stream>
void ProcMonitor::skip_fields(Stream& stream, size_t count) {
    std::string tmp;
    for (int i = 0; i < count; ++i) {
        stream >> tmp;
    }
}

template <typename T, typename Stream>
T ProcMonitor::read_from_stream(Stream &stream) {
    T tmp;
    stream >> tmp;
    return tmp;
}
