#pragma once
#include <nlohmann/json.hpp>
#include <string>

#include "collectors/structs.hpp"
#include "json_serializer.hpp"

using json = nlohmann::json;

struct SystemSnapshot;

class Serializer {

public:
    static std::string serialize(const SystemSnapshot& snapshot);
};
