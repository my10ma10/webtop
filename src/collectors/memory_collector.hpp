#pragma once
#include <unordered_map>
#include <string>

#include "structs.hpp"

/**
 * @brief Читает /proc/meminfo и собирает информацию о памяти
 */
class MemoryCollector {

public:
    MemoryInfo collect();

private:
    std::unordered_map<std::string, uint64_t> parseMemInfo();
};