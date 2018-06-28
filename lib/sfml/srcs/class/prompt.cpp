//
// EPITECH PROJECT, 2018
// arcade
// File description:
// SFML LIB PROMPT
//

#include "sfml.hpp"

void u_sfml::addCharacterToPrompt(char character)
{
	if (!(this->playerName.size() < 20))
		return ;
	this->playerName.push_back(character);
}

void u_sfml::displayPrompt()
{
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(200, 50));
	rectangle.setPosition(sf::Vector2f(this->width / 2 - 100, 150));
	rectangle.setOutlineThickness(5);
	rectangle.setOutlineColor(sf::Color::Black);
	this->window.draw(rectangle);
	this->drawText("ARIAL", this->playerName, 20, sf::Color::Black,
		       sf::Color::White, sf::Vector2f(this->width / 2 - 95, 160));
}
