#include "process_info.hpp"
#include <cmath>
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
        } 
        else if (kb >= 1024) {
            return std::format("{:.1f}m", kb / 1024.0);
        }
        return std::to_string(kb) + "k";
    };
   
    os << std::setw(7) << info.pid << ' '
       << std::left << std::setw(10) << info.user << std::right << ' '
       << std::setw(3) << info.priority << ' '
       << std::setw(3) << info.nice << ' '
       << std::setw(8) << format_mem(info.virt) << ' '
       << std::setw(8) << info.res << ' '
       << std::setw(8) << info.shr << ' '
       << state_to_char.at(info.state) << ' '
       << std::fixed << std::setprecision(1)
       << std::setw(5) << info.cpu_usage.total << ' '
       << std::setw(5) << info.mem_usage.total << ' '
       << std::setw(8) << format_cpu_time(info.cpu_ticks)
       << info.command;
    return os;
}


std::string format_cpu_time(uint64_t ticks) {
    const long ticks_per_sec = sysconf(_SC_CLK_TCK);
    double total_sec = static_cast<double>(ticks) / ticks_per_sec;

    int minutes = total_sec / 60;
    auto rem = std::fmod(total_sec, 60.0);

    int seconds = static_cast<int>(rem);
    int hundredths = static_cast<int>((rem - seconds) * 100);

    return std::format(
        "{}:{:02}.{:02}",
        minutes,
        seconds,
        hundredths
    );
}