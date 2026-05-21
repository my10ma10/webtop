#include "monitor_engine.hpp"
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <ranges>
#include <iostream>
#include <sstream>

#include "stream_manage.hpp"

namespace fs = std::filesystem;

void ProcMonitor::updateInfo() {
    proc_info_.clear();

    auto pids = iterateProcesses();

    for (const pid_t& pid : pids) {
        readProc(pid);
        std::cout << proc_info_ << std::endl;
    }
    std::cout << "\n" << '-' * 60 << std::endl;
}

void ProcMonitor::readProc(pid_t pid) {
    std::ifstream file(std::string("/proc/") + std::to_string(pid) + "/stat");
    std::string info_line;
    std::getline(file, info_line);

    parseProcLine(info_line);
}

std::vector<pid_t> ProcMonitor::iterateProcesses() {
    std::vector<pid_t> pids;
    for (const auto& entry : fs::directory_iterator("/proc")) {
        if (!entry.is_directory()) {
            continue;
        }

        auto name = entry.path().filename().string();

        if (std::ranges::all_of(name, ::isdigit)) {
            pids.emplace_back(std::stoi(name));
        }
    }
    return pids;
}

void ProcMonitor::parseProcLine(const std::string& info_line) {
    auto open_br = info_line.find('(');
    auto close_br = info_line.rfind(')');

    if (open_br == std::string::npos || close_br == std::string::npos) return;

    proc_info_.pid = std::stoi(info_line.substr(0, open_br));
    proc_info_.command = info_line.substr(open_br, close_br - open_br + 1);

    parseRestLine(info_line, close_br + 1);
}

void ProcMonitor::parseRestLine(const std::string& info_line, std::size_t start_pos) {
    auto rest = info_line.substr(start_pos);

    std::istringstream iss(rest);
    
    proc_info_.state = char_to_state.at(stream::readStream<char>(iss));

    stream::skipFields(iss, 10);

    auto utime = stream::readStream<unsigned long>(iss);  // 14
    auto stime = stream::readStream<unsigned long>(iss);  // 15
    proc_info_.cpu_ticks = utime + stime;

    stream::skipFields(iss, 2);

    proc_info_.priority = stream::readStream<uint64_t>(iss); // 18
    proc_info_.nice = stream::readStream<uint64_t>(iss);     // 19

    stream::skipFields(iss, 3);

    proc_info_.virt = stream::readStream<int>(iss);   // 23
}
