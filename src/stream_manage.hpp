#pragma once
#include <cstdint>
#include <string>

namespace stream {
template <typename Stream>
void skipFields(Stream& stream, size_t count) {
    std::string tmp;
    for (int i = 0; i < count; ++i) {
        stream >> tmp;
    }
}

template <typename T, typename Stream>
T readStream(Stream& stream) {
    T tmp;
    stream >> tmp;
    return tmp;
}



}