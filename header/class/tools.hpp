//
// EPITECH PROJECT, 2018
// arcade
// File description:
// tools
//

#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <iostream>

namespace arcade {
	class Tools {
	public:
		Tools();
		~Tools();
		static std::string my_substr(const std::string &src, const std::string &after,
					     const std::string &before);
	};
}

#endif /* !TOOLS_HPP_*/
