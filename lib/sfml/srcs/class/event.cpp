//
// EPITECH PROJECT, 2018
// arcade
// File description:
// SFML LIB EVENT
//

#include "sfml.hpp"

void u_sfml::keyManager(sf::Keyboard::Key &code)
{
	if (code == sf::Keyboard::BackSpace && this->playerName.size() > 1) {
		this->playerName.erase(this->playerName.size() - 1);
		this->playerName.pop_back();
	} else
		this->eventKey = code;
}

void u_sfml::sfml_event(sf::Event &event)
{
	if (event.type == sf::Event::Closed) {
		this->closeWindow();
		this->isExit = true;
	} else if (event.type == sf::Event::MouseButtonPressed)
		this->buttonClick();
	else if (event.type == sf::Event::KeyPressed)
		this->keyManager(event.key.code);
	else if (this->state == arcade::MENU && event.type == sf::Event::TextEntered)
		this->addCharacterToPrompt(static_cast<char>(event.text.unicode));
}
