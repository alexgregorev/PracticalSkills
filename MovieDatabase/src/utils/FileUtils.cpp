#include "utils/FileUtils.h"
#include <fstream>

std::vector<char> load_file(std::string_view path)
{
    std::vector<char> data;

    std::ifstream file(path.data(), std::ios::binary | std::ios::ate);
    if (!file.is_open()) return data;

    auto size = file.tellg();
    file.seekg(0);

    data.resize(size);
    file.read(data.data(), size);

    return data;
}