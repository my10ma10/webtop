#pragma once
#include "structs.hpp"

/**
 * @class Собирает состояние CPU и сравнивает с предыдущим для вычисления загруженности CPU
 * 
 */
class CpuCollector {
    std::vector<CpuStatSnapshot> previous_stats_;

public:
    CpuUsage collect();

private:
    std::vector<CpuStatSnapshot> readStat();

    CpuStatSnapshot parseCpuLine(const std::string& line);

    uint64_t totalTime(const CpuStatSnapshot& stat);
    uint64_t idleTime(const CpuStatSnapshot& stat);
};