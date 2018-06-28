//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml lib button
//

#include "sfml.hpp"

void u_sfml::mouseAction()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(this->window);
	sf::Vector2f position;
	sf::FloatRect localBound;

	for (auto button = this->buttons_games.begin() ;
	     button != this->buttons_games.end() ; ++button) {
		localBound = button->second.getLocalBounds();
		position = button->second.getPosition();
		if ((mouse.x >= position.x && mouse.x <= position.x + localBound.width)
		    && (mouse.y >= position.y && mouse.y <= position.y + localBound.height)) {
			button->second.setOutlineColor(sf::Color::Red);
			this->indexBackgrounds = std::string(button->first);
			break;
		} else {
			button->second.setOutlineColor(sf::Color::Black);
			this->indexBackgrounds = DEFAULT;
		}
	}

	for (auto button = this->buttons_graphics.begin() ;
	     button != this->buttons_graphics.end() ; ++button) {
		localBound = button->second.getLocalBounds();
		position = button->second.getPosition();
		if ((mouse.x >= position.x && mouse.x <= position.x + localBound.width)
		    && (mouse.y >= position.y && mouse.y <= position.y + localBound.height)) {
			button->second.setOutlineColor(sf::Color::Red);
		} else {
			button->second.setOutlineColor(sf::Color::Black);
		}
	}
}

void u_sfml::buttonClick()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(this->window);
	sf::Vector2f position;
	sf::FloatRect localBound;

	for (auto button = this->buttons_games.begin() ;
	     button != this->buttons_games.end() ; ++button) {
		localBound = button->second.getLocalBounds();
		position = button->second.getPosition();
		if ((mouse.x >= position.x && mouse.x <= position.x + localBound.width)
		    && (mouse.y >= position.y && mouse.y <= position.y + localBound.height)) {
			this->GamePathName = GAMES_LIB_PATH + std::string(button->first) + GAMES_LIB_EXT;
			this->playSound("click");
			break ;
		}
	}
	for (auto button = this->buttons_graphics.begin() ;
	     button != this->buttons_graphics.end() ; ++button) {
		localBound = button->second.getLocalBounds();
		position = button->second.getPosition();
		if ((mouse.x >= position.x && mouse.x <= position.x + localBound.width)
		    && (mouse.y >= position.y && mouse.y <= position.y + localBound.height)) {
			this->GraphicsPathName = GRAPHICS_LIB_PATH + std::string(button->first) + GRAPHICS_LIB_EXT;
			this->playSound("click");
			break ;
		}
	}
}

void u_sfml::createButtons(std::map<std::string, void *> &lib_name,
			   std::map<const std::string, sf::RectangleShape> &container,
			   const std::string &after, const std::string &before, sf::Vector2f position)
{
	std::string str;

	for (auto game_name = lib_name.begin() ; game_name != lib_name.end() ; ++game_name) {
		sf::RectangleShape rectangle;
		str = my_substr(game_name->first, after, before);
		rectangle.setSize(sf::Vector2f(200, 50));
		rectangle.setPosition(position);
		rectangle.setOutlineThickness(5);
		container[str] = rectangle;
		position.y += 100;
	}
}
