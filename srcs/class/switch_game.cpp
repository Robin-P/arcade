//
// Created by student on 03/04/18.
//

#include "console.hpp"

void arcade::Console::nextGame(std::string &index)
{
	size_t count = 1;
	auto lib = this->games.begin();

	for (; lib != this->games.end() && index != lib->first; ++lib, ++count);
	if (lib->first == index && count <= this->games.size() - 1) {
		++lib;
		this->launchGame("launch", lib->second);
		std::cerr << std::endl;
		index = lib->first;
		std::cerr << std::endl;
	} else {
		lib = this->games.begin();
		this->launchGame("launch", lib->second);
		std::cerr << std::endl;
		index = lib->first;
		std::cerr << std::endl;
	}
}

void arcade::Console::previousGame(std::string &index)
{
	size_t count = 1;

	auto lib = this->games.begin();
	for (; lib != this->games.end() && index != lib->first; ++lib, ++count);
	if (lib->first == index && count > 1) {
		--lib;
		this->launchGame("launch", lib->second);
		std::cerr << std::endl;
		index = lib->first;
		std::cerr << std::endl;
	} else if (lib->first == index && count == 1) {
		lib = this->games.end();
		--lib;
		this->launchGame("launch", lib->second);
		std::cerr << std::endl;
		index = lib->first;
		std::cerr << std::endl;
	}
}

void arcade::Console::changeGame(std::unique_ptr<arcade::IGame> &game,
						  arcade::keys &key, std::string &index)
{
	game.release();
	if (key == arcade::NEXT_GAME)
		this->nextGame(index);
	else
		this->previousGame(index);
	game.swap(this->game_ptr());
	if (game->type != arcade::libType::GAME_LIB)
		throw (arcade::Exception("Console", "Invalid lib: " + index));
}