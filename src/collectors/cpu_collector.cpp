#include "cpu_collector.hpp"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <vector>

#include "stream_manage.hpp"

CpuUsage CpuCollector::collect() {
    auto current_stats = readStat();

    if (previous_stats_.empty()) {
        previous_stats_ = current_stats;
        return CpuUsage{};
    }

    CpuUsage usage;

    for (int i = 0; i < current_stats.size(); ++i) {
        const auto& previous_stat = previous_stats_[i];
        const auto& current_stat = current_stats[i];

        uint64_t previous_total = totalTime(previous_stat);
        uint64_t current_total = totalTime(current_stat);
        
        uint64_t previous_idle = idleTime(previous_stat);
        uint64_t current_idle = idleTime(current_stat);

        uint64_t total_delta_time = current_total - previous_total;
        uint64_t idle_delta_time = current_idle - previous_idle;
        uint64_t active_delta_time = total_delta_time - idle_delta_time;


        float cpu_usage = 0.0f;
        if (total_delta_time != 0) {
            cpu_usage = 100.0f * static_cast<float>(active_delta_time) 
                        / static_cast<float>(total_delta_time);
        }

        if (i == 0) {
            usage.total = cpu_usage;
        }
        else {
            usage.cores.push_back(CpuCoreUsage{
                .usage_percent = cpu_usage
            });
        }
    }
    previous_stats_ = current_stats;

    return usage;
}

std::vector<CpuStatSnapshot> CpuCollector::readStat() {
    std::ifstream file("/proc/stat");

    std::vector<CpuStatSnapshot> stats;
    std::string cpu_stat_line;

    while (std::getline(file, cpu_stat_line)) {
        if (!cpu_stat_line.starts_with("cpu")) {
            break;
        }
        stats.emplace_back(parseCpuLine(cpu_stat_line));
    }

    return stats;
}

/**
 * @brief Собирает статистику, сравнивает с предыдущей, 
 * вычисляет разницу между previous и current и сохраняет новую статистику 
 */
CpuStatSnapshot CpuCollector::parseCpuLine(const std::string& line) {
    std::istringstream ss(line);

    CpuStatSnapshot stat;

    ss >> stat.cpu_name
       >> stat.user
       >> stat.nice
       >> stat.system
       >> stat.idle
       >> stat.iowait
       >> stat.irq
       >> stat.softirq
       >> stat.steal;

    return stat;
}

uint64_t CpuCollector::totalTime(const CpuStatSnapshot& stat) {
    return stat.user
         + stat.nice
         + stat.system
         + stat.idle
         + stat.iowait
         + stat.irq
         + stat.softirq
         + stat.steal;
}


uint64_t CpuCollector::idleTime(const CpuStatSnapshot& stat) {
    return stat.idle + stat.iowait;
}