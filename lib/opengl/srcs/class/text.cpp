//
// EPITECH PROJECT, 2018
// arcade
// File description:
// opengl lib text
//

#include "opengl.hpp"

void u_opengl::drawMenuText()
{
	float x, y;
	std::string title = "ARCADE";

	x = (this->width / 2) - ((title.size() * 100 / 2) / 2);
	y = 20;
	this->drawText("ARIAL", title, 100, sf::Color::Black,
		       sf::Color::White, sf::Vector2f(x, y));
	for (auto button = this->buttons_games.begin() ;
	     button != this->buttons_games.end() ; ++button) {
		sf::Vector2f position = button->second.getPosition();

		position.x += 20;
		this->window.draw(button->second);
		this->drawText("ARIAL", button->first, 40, sf::Color::Red,
			       sf::Color::White, position);
	}
	for (auto button = this->buttons_graphics.begin() ;
	     button != this->buttons_graphics.end() ; ++button) {
		sf::Vector2f position = button->second.getPosition();

		position.x += 20;
		this->window.draw(button->second);
		this->drawText("ARIAL", button->first, 40, sf::Color::Red,
			       sf::Color::White, position);
	}
}

void u_opengl::drawText(const std::string &font_name, const std::string &line, const size_t &size,
		      const sf::Color &outlineColor, const sf::Color &textColor,
		      const sf::Vector2f &position)
{
	sf::Text text;
	std::unique_ptr<sf::Font> &font = this->getFont(font_name);

	text.setFont(*font);
	text.setString(line);
	text.setCharacterSize(size);
	text.setOutlineThickness(2);
	text.setOutlineColor(outlineColor);
	text.setFillColor(textColor);
	text.setPosition(position);
	this->window.draw(text);
}
