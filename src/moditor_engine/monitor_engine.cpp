#include "monitor_engine.hpp"
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <ranges>
#include <iostream>

namespace fs = std::filesystem;

void ProcMonitor::updateInfo() {
    proc_info_.clear();

    auto pids = iterateProcesses();

    for (const pid_t& pid : pids) {
        readProc(pid);
        std::cout << proc_info_ << std::endl;
    }
}

void ProcMonitor::readProc(pid_t pid) {
    std::ifstream file(std::string("/proc/") + std::to_string(pid) + "/stat");
    file >> proc_info_.pid;

    std::string cmd_with_brackets;
    file >> cmd_with_brackets;
    if (cmd_with_brackets.size() > 2) {
        proc_info_.command = cmd_with_brackets.substr(1, cmd_with_brackets.size() - 2);
    }
    else {
        throw std::out_of_range(std::string("Too short cmd name: ") + "'" + cmd_with_brackets + "'");
    }
    
    char st;
    file >> st;
    proc_info_.state = char_to_state[st];

    


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
