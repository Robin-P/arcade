//
// EPITECH PROJECT, 2018
// arcade
// File description:
// exception
//

#include "exception.hpp"

using u_exception = arcade::Exception;

u_exception::Exception(const std::string &e_from, const std::string &e_message)
{
	this->from = e_from;
	this->message = e_message;
}

u_exception::~Exception()
{
}

std::string u_exception::what()
{
	return "Error: " + this->from + ": " + this->message;
}
