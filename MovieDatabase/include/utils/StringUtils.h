#pragma once
#include <string>
#include <vector>

std::vector<std::string> split(std::string text, char delimiter);
bool starts_with(std::string_view text, std::string_view part);
std::string trim(std::string_view text);
