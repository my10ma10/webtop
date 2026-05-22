#include "process_collector.hpp"
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <ranges>
#include <thread>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include "stream_manage.hpp"

namespace fs = std::filesystem;

std::vector<ProcessInfo> ProcessCollector::collect() {
    auto pids = enumeratePids();
    uint64_t current_total_cpu_ticks = readTotalCpuTicks();

    std::vector<ProcessInfo> infos;
    infos.reserve(pids.size());


    for (const pid_t pid : pids) {
        try {
            auto snapshot = readProc(pid);

            ProcessSnapshot* prev = nullptr;

            auto it = previous_.find(pid);
            if (it != previous_.end())  {
                prev = &it->second;
            }

            infos.push_back(snapshotToInfo(snapshot, prev, current_total_cpu_ticks)); 

            previous_[pid] = snapshot;
        }
        catch (...) {
            continue;
        }
    }
    previous_total_cpu_ticks_ = current_total_cpu_ticks;
    return infos;
}

ProcessSnapshot ProcessCollector::readProc(pid_t pid) {
    std::ifstream stat_file(std::string("/proc/") + std::to_string(pid) + "/stat");
    if (!stat_file.is_open()) {
        throw std::runtime_error("Cannot open /proc stat");
    }

    std::string info_line;
    std::getline(stat_file, info_line);

    auto snapshot = parseProcLine(info_line);
    snapshot.uid = readUid(pid);


    std::ifstream statm_file("/proc/" + std::to_string(pid) + "/statm");
    if (!statm_file.is_open()) {
        throw std::runtime_error("Cannot open /proc statm");
    }

    uint64_t size;
    statm_file >> size >> snapshot.rss_pages >> snapshot.shared_pages;

    return snapshot;
}

std::vector<pid_t> ProcessCollector::enumeratePids() {
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

uid_t ProcessCollector::readUid(pid_t pid) {
    std::ifstream file("/proc/" + std::to_string(pid) + "/status");

    std::string key;
    while (file >> key) {
        if (key == "Uid:") {
            uid_t uid;
            file >> uid;
            return uid;
        }
        std::string line;
        std::getline(file, line);
    }
    return 0;
}

std::string ProcessCollector::uidToUsername(uid_t uid) {
    passwd* pw = getpwuid(uid);

    if (!pw) {
        return std::to_string(uid);
    }

    return pw->pw_name;
}

ProcessInfo ProcessCollector::snapshotToInfo(
    const ProcessSnapshot& current, 
    const ProcessSnapshot* previous,
    uint64_t current_total_cpu_ticks
) {
    ProcessInfo info;

    constexpr uint64_t KB = 1024;
    const int64_t page_size = sysconf(_SC_PAGESIZE);


    info.pid = current.pid;
    info.user = uidToUsername(current.uid);

    info.priority = current.priority;
    info.nice = current.nice;
    info.command = current.command;
    info.cpu_ticks = current.cpu_ticks;


    info.virt = static_cast<int>(current.virt_size / KB);

    info.res = static_cast<int>(
            current.rss_pages * page_size / KB
        );

    info.shr = static_cast<int>(
            current.shared_pages * page_size / KB
        );

    info.cpu_usage.total = calculateCpuUsage(current, previous);

    auto it = char_to_state.find(current.state);
    if (it != char_to_state.end()) {
        info.state = it->second;
    }
    else {
        info.state = ProcessState::Unknown;
    }

    return info;
}

uint64_t ProcessCollector::readTotalCpuTicks() {
    std::ifstream file("/proc/stat");
    auto st = stream::readCpuStat(file);

    return 
        st.user + st.nice + 
        st.system + st.idle + 
        st.iowait + st.irq + 
        st.softirq + st.steal;
}

float ProcessCollector::calculateCpuUsage(
    const ProcessSnapshot& current,
    const ProcessSnapshot* previous
) {
    if (!previous || previous_total_cpu_ticks_ == 0) {
        return 0.0f;
    }

    uint64_t current_total_cpu_ticks = readTotalCpuTicks();

    auto current_ticks = current.utime + current.stime;
    auto previous_ticks = previous->utime + previous->stime;
    auto process_delta = current_ticks - previous_ticks;
    auto total_delta = current_total_cpu_ticks - previous_total_cpu_ticks_;

    

    return static_cast<float>(process_delta) * 100.0f * std::thread::hardware_concurrency()
           / static_cast<float>(total_delta);
}

ProcessSnapshot ProcessCollector::parseProcLine(const std::string& info_line) {
    auto open_br = info_line.find('(');
    auto close_br = info_line.rfind(')');

    if (open_br == std::string::npos || close_br == std::string::npos) {
        throw std::runtime_error("Invalid /proc stat format");
    };

    ProcessSnapshot snapshot;
    snapshot.pid = std::stoi(info_line.substr(0, open_br));
    snapshot.command = info_line.substr(open_br + 1, close_br - open_br - 1);

    parseRestLine(info_line, close_br + 1, snapshot);
    return snapshot;
}

void ProcessCollector::parseRestLine(const std::string& info_line, std::size_t start_pos, ProcessSnapshot& snapshot) {
    auto rest = info_line.substr(start_pos);
    
    std::istringstream iss(rest);
    
    snapshot.state = stream::readStream<char>(iss);

    stream::skipFields(iss, 10);

    snapshot.utime = stream::readStream<uint64_t>(iss);  // 14
    snapshot.stime = stream::readStream<uint64_t>(iss);  // 15
    snapshot.cpu_ticks = snapshot.utime + snapshot.stime;

    stream::skipFields(iss, 2);

    snapshot.priority = stream::readStream<int64_t>(iss); // 18
    snapshot.nice = stream::readStream<int64_t>(iss);     // 19

    stream::skipFields(iss, 2);

    snapshot.starttime = stream::readStream<uint64_t>(iss); // 22
    snapshot.virt_size = stream::readStream<uint64_t>(iss); // 23
}
