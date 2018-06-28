//
// EPITECH PROJECT, 2018
// arcade
// File description:
// tools
//

#include "tools.hpp"

std::string arcade::Tools::my_substr(const std::string &str, const std::string &after,
				     const std::string &extension)
{
	std::string result = str;

        result = result.substr(result.find(after) + after.size());
        result = result.substr(0, result.size() - extension.size());
        return result;
}
