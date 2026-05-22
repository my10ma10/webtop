#include "serializer.hpp"

std::string Serializer::serialize(const SystemSnapshot& snapshot) {
    json j = snapshot;

    return j.dump(4);
}
