//
// EPITECH PROJECT, 2018
// arcade
// File description:
// exception
//

#ifndef EXCEPTION_ARCADE_HPP_
#define EXCEPTION_ARCADE_HPP_

#include <iostream>

namespace arcade {
	class Exception : public std::exception {
	public:
		Exception(const std::string &from, const std::string &message);
		~Exception() override;
		std::string what();
	private:
		std::string message;
		std::string from;
	};
}

#endif /* !EXCEPTION_ARCADE_HPP */
