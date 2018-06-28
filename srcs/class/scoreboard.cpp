//
// Created by student on 03/04/18.
//

#include <sstream>
#include <fstream>
#include "console.hpp"
#include "tools.hpp"

void arcade::Console::setScore(std::string &game_lib_name,
						 std::unique_ptr<arcade::IGraphics> &graphics,
						 const int &score)
{
	std::string game_name = Tools::my_substr(game_lib_name, GAMES_LIB_PATH,
											 GAMES_LIB_EXT);
	std::ifstream fileR(SCOREBOARD + game_name + "/" + SCORE_FILE);
	std::string line, file_player;
	int file_score = 0, index = 0;

	if (!fileR.is_open())
		throw arcade::Exception("CONSOLE", +SCOREBOARD + game_name + "/" +
										   SCORE_FILE " is missing.");
	while (!fileR.eof()) {
		getline(fileR, line);
		std::stringstream ss;
		if (line.empty());
		else if (index == 0) {
			ss << line.substr(5, line.size() - 5); // "name:"
			ss >> file_player;
		} else if (index == 1) {
			ss << line.substr(6, line.size() - 6); // "score:"
			ss >> file_score;
		}
		++index;
	}
	fileR.close();
	std::ofstream fileW(SCOREBOARD + game_name + "/" + SCORE_FILE);
	if (!fileW.is_open())
		throw arcade::Exception("CONSOLE", "Setting score failed.");
	file_player = (score > file_score ? graphics->playerName : file_player);
	file_score = (score > file_score ? score : file_score);
	fileW << "name: " << file_player << std::endl << "score: " << file_score
		  << std::endl;
	fileW.close();
}
