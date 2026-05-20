#include "process_info.hpp"
#include <format>
#include <iostream>
#include <iomanip>

void ProcessInfo::clear() {
    *this = ProcessInfo{};
}

std::ostream& operator<<(std::ostream& os, const ProcessInfo& info) {
    auto format_mem = [](int kb) -> std::string {
        if (kb >= 1024 * 1024) {
            return std::format("{:.1f}g", kb / (1024.0 * 1024.0));
        } else if (kb >= 1024) {
            return std::format("{:.1f}m", kb / 1024.0);
        }
        return std::to_string(kb) + "k";
    };

    auto total_sec = info.time_plus.tv_sec;
    auto minutes = total_sec / 60;
    auto seconds = total_sec % 60;
    auto hundredths = info.time_plus.tv_usec / 10000;

    os << std::setw(7) << info.pid << ' '
       << std::left << std::setw(10) << info.user << std::right << ' '
       << std::setw(3) << info.pr << ' '
       << std::setw(3) << info.ni << ' '
       << std::setw(8) << format_mem(info.virt) << ' '
       << std::setw(8) << info.res << ' '
       << std::setw(8) << info.shr << ' '
       << state_to_char[info.state] << ' '
       << std::fixed << std::setprecision(1)
       << std::setw(5) << info.cpu_percent << ' '
       << std::setw(5) << info.mem_persent << ' '
       << std::setw(2) << std::setfill('0') << minutes << ':'
       << std::setw(2) << seconds << '.'
       << std::setw(2) << hundredths << std::setfill(' ') << ' '
       << info.command;
    return os;
}