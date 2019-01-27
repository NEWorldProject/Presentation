#pragma once

#include <vector>
#include <fstream>

namespace Presentation::Utils {
    static std::vector<char> LoadFile(const std::string& filename) {
        if (std::ifstream file(filename, std::ios::ate | std::ios::binary); file.good()) {
            auto size = (size_t) file.tellg();
            std::vector<char> buffer(size);
            file.seekg(0);
            file.read(buffer.data(), size);
            return buffer;
        }
        throw std::runtime_error("File Open Failure");
    }
}
