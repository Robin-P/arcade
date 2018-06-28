//
// EPITECH PROJECT, 2018
// arcade
// File description:
// LIB SFML MENU
//

#include "sfml.hpp"

void u_sfml::initMenu(std::map<std::string, void *> &game_lib_name,
		      std::map<std::string, void *> &graphics_lib_name)
{
	this->GraphicsPathName = "";
	this->GamePathName = "";
	this->createButtons(game_lib_name, this->buttons_games, GAMES_LIB_PATH, GAMES_LIB_EXT,
			    sf::Vector2f(this->width - 300, 300));
	this->createButtons(graphics_lib_name, this->buttons_graphics,
			    GRAPHICS_LIB_PATH, GRAPHICS_LIB_EXT,
			    sf::Vector2f(100, 300));
	this->createBackgrounds(game_lib_name);
	this->createScoreboard(game_lib_name);
}

arcade::menuLeave u_sfml::leaveMenu()
{
	if (!this->GamePathName.empty()) {
		this->cleanRessources();
		if (!GamePathName.empty()) {
			this->createSound("start", SOUND_PATH +
					  my_substr(this->GamePathName, GAMES_LIB_PATH, GAMES_LIB_EXT) +
					  "/start.wav");
			this->playSound("start");
		}
		return {arcade::menuLeave::GAME, this->GamePathName};
	} else if (!this->GraphicsPathName.empty())
		return {arcade::menuLeave::GRAPHIC, this->GraphicsPathName};
	return {arcade::menuLeave::EXIT, std::string()};
}

arcade::menuLeave u_sfml::menu(std::map<std::string, void *> &game_lib_name,
			 std::map<std::string, void *> &graphics_lib_name)
{
	sf::Event event{};

	this->state = arcade::MENU;
	this->initMenu(game_lib_name, graphics_lib_name);
	this->createSound("click", SOUND_PATH + std::string("/click.ogg"));
	while (this->state == arcade::MENU && this->window.isOpen()
	       && this->GamePathName.empty() && this->GraphicsPathName.empty()) {
		this->clearWindow();
		this->mouseAction();
		std::unique_ptr<sf::Sprite> &background = this->backgrounds[this->indexBackgrounds];
		this->window.draw(*background);
		this->drawMenuText();
		this->displayPrompt();
		this->displayScoreboard("ARIAL", this->indexBackgrounds, 40,
					sf::Color::Black, sf::Color::White,
					sf::Vector2f(this->width / 2 - 125, this->height / 2));
		this->displayWindow();
		while (this->window.pollEvent(event))
			this->sfml_event(event);
	}
	this->clearWindow();
	return this->leaveMenu();
}
