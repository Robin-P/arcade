//
// EPITECH PROJECT, 2018
// ARCADE
// File description:
// SFML LIB FONT
//

#include "opengl.hpp"

std::unique_ptr<sf::Font> &u_opengl::getFont(const std::string &name)
{
	if (this->fonts.find(name) == this->fonts.end())
		throw arcade::Exception("SFML LIB", std::string("Unknown font: ")
					+ name);
	return this->fonts[name];
}

void u_opengl::addFont(const std::string &key, const std::string &maccro)
{
	std::unique_ptr<sf::Font> font = std::make_unique<sf::Font>();

	font->loadFromFile(maccro);
	this->fonts[key] = std::move(font);
}

void u_opengl::addFont(const std::string &key, std::unique_ptr<sf::Font> &font)
{
	this->fonts[key] = std::move(font);
}
