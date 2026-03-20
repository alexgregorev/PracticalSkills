#pragma once
#include <string>
#include <vector>
#include <optional>

struct media
{
    unsigned int id;
    unsigned int movie_id;
    std::string name;
    std::optional<std::string> text;
    std::vector<char> blob;
};

using media_list = std::vector<media>;
