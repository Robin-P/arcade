//
// EPITECH PROJECT, 2018
// arcade
// File description:
// LIB SFML SCOREBOARD
//

#include <sstream>
#include <fstream>
#include "opengl.hpp"

std::string u_opengl::getScore(std::string &game_name)
{
	std::string path = SCOREBOARD + game_name + "/" + SCORE_FILE;
	std::ifstream file(path);
	std::string line, player, score;
	size_t index = 0;

	if (!file.is_open())
		throw arcade::Exception("LIB SFML", path + " is missing.");
	while (!file.eof()) {
		getline(file, line);
		std::stringstream ss;
		if (line.empty());
		else if (index == 0) {
			ss << line.substr(5, line.size() - 5); // "name:"
			ss >> player;
		}
		else if (index == 1) {
			ss << line.substr(6, line.size() - 6); // "score:"
			ss >> score;
		}
		++index;
	}
	return player + ": " + score;
}

void u_opengl::displayScoreboard(const std::string &font_name, const std::string &game_selected,
			       const size_t &size, const sf::Color &first, const sf::Color &second,
			       sf::Vector2f position)
{
	sf::RectangleShape rectangle;
	std::string result = this->scoreboards[game_selected];

	if (game_selected != DEFAULT && !result.empty()) {
		rectangle.setSize(sf::Vector2f(250, 50));
		rectangle.setPosition(position);
		rectangle.setOutlineThickness(5);
		rectangle.setOutlineColor(sf::Color::Red);
		this->window.draw(rectangle);
		position.x += 10;
		this->drawText(font_name, result, size, first, second, position);
		position.y -= 40;
		this->drawText(font_name, "Highscore:", size - 10, first, second, position);
	}
}

void u_opengl::createScoreboard(std::map<std::string, void *> &game_lib_name)
{
	for (auto game = game_lib_name.begin() ; game != game_lib_name.end() ; ++game) {
		std::string game_name = my_substr(game->first, GAMES_LIB_PATH, GAMES_LIB_EXT);
		this->scoreboards[game_name] = this->getScore(game_name);
	}
}
