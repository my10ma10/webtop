#pragma once
#include <nlohmann/json.hpp>
#include "system_monitor/system_snapshot.hpp"

using json = nlohmann::json;

inline void to_json(json& j, const CpuCoreUsage& c) {
    j = {
        {"id", c.core_id.value()},
        {"usage_percent", c.usage_percent}
    };
}

inline void from_json(const json& j, CpuCoreUsage& c) {
    j.at("id").get_to(c.core_id.value());
    j.at("usage_percent").get_to(c.usage_percent);
}

inline void to_json(json& j, const CpuUsage& c) {
    j = {
        {"total_usage_percent", c.total},
        {"cores", c.cores}
    };
}

inline void from_json(const json& j, CpuUsage& c) {
    j.at("total_usage_percent").get_to(c.total);
    j.at("cores").get_to(c.cores);
}

inline void to_json(json& j, const MemoryInfo& m) {
    j = {
        {"total_kb", m.total_kb},
        {"used_kb", m.used_kb},
        {"available_kb", m.available_kb},
        {"free_kb", m.free_kb},

        {"usage_percent", m.usage_percent}
    };
}

inline void from_json(const json& j, MemoryInfo& m) {
    j.at("total_kb").get_to(m.total_kb);
    j.at("used_kb").get_to(m.used_kb);
    j.at("available_kb").get_to(m.available_kb);
    j.at("free_kb").get_to(m.free_kb);

    j.at("usage_percent").get_to(m.usage_percent);
}

inline void to_json(json& j, const ProcessState& state) {
    auto it = state_to_char.find(state);

    if (it != state_to_char.end()) {
        j = std::string(1, it->second);
    }
    else {
        j = "Unknown";
    }
}

inline void from_json(const json& j, ProcessState& state) {
    if (!j.is_string()) {
        state = ProcessState::Unknown;
        return;
    }

    const auto str = j.get<std::string>();

    if (str.size() != 1) {
        state = ProcessState::Unknown;
        return;
    }

    auto it = char_to_state.find(str[0]);

    if (it != char_to_state.end()) {
        state = it->second;
    }
    else {
        state = ProcessState::Unknown;
    }
}

inline void to_json(json& j, const ProcessInfo& p) {
    j = {
        {"pid", p.pid},

        {"user", p.user},

        {"priority", p.priority},
        {"nice", p.nice},

        {"virt_kb", p.virt},
        {"res_kb", p.res},
        {"shr_kb", p.shr},

        {"state", p.state},

        {"cpu_usage", p.cpu_usage},
        {"memory_usage", p.mem_usage},

        {"cpu_ticks", p.cpu_ticks},

        {"command", p.command}
    };
}

inline void from_json(const json& j, ProcessInfo& p) {
    j.at("pid").get_to(p.pid);

    j.at("user").get_to(p.user);

    j.at("priority").get_to(p.priority);
    j.at("nice").get_to(p.nice);

    j.at("virt_kb").get_to(p.virt);
    j.at("res_kb").get_to(p.res);
    j.at("shr_kb").get_to(p.shr);

    j.at("state").get_to(p.state);

    j.at("cpu_usage").get_to(p.cpu_usage);
    j.at("memory_usage").get_to(p.mem_usage);

    j.at("cpu_ticks").get_to(p.cpu_ticks);

    j.at("command").get_to(p.command);
}

inline void to_json(json& j, const SystemSnapshot& s) {
    j = {
        {"timestamp", s.timestamp},
        {"cpu", s.cpu_usage},
        {"memory", s.memory_info},
        {"processes", s.processes}
    };
}

inline void from_json(const json& j, SystemSnapshot& s) {
    j.at("timestamp").get_to(s.timestamp);
    j.at("cpu").get_to(s.cpu_usage);
    j.at("memory").get_to(s.memory_info);
    j.at("processes").get_to(s.processes);
}