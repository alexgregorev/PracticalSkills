#include "utils/StringUtils.h"
#include <sstream>

std::vector<std::string> split(std::string text, char delimiter)
{
    std::stringstream ss(text);
    std::vector<std::string> tokens;
    std::string token;

    while (std::getline(ss, token, delimiter))
        if (!token.empty())
            tokens.push_back(token);

    return tokens;
}

bool starts_with(std::string_view text, std::string_view part)
{
    return text.find(part) == 0;
}

std::string trim(std::string_view text)
{
    auto first = text.find_first_not_of(' ');

    // 🔥 FIX: обработка строки из одних пробелов
    if (first == std::string_view::npos)
        return "";

    auto last = text.find_last_not_of(' ');
    return std::string(text.substr(first, last - first + 1));
}