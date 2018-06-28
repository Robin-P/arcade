//
// Created by student on 03/04/18.
//

#include "console.hpp"

void arcade::Console::nextLib(std::string &index)
{
	size_t count = 1;
	auto lib = this->graphics.begin();

	for (; lib != this->graphics.end() && index != lib->first; ++lib, ++count);
	if (lib->first == index && count <= this->graphics.size() - 1) {
		++lib;
		this->launchGraphics("launch", lib->second);
		std::cerr << std::endl;
		index = lib->first;
		std::cerr << std::endl;
	} else {
		lib = graphics.begin();
		this->launchGraphics("launch", lib->second);
		std::cerr << std::endl;
		index = lib->first;
		std::cerr << std::endl;
	}
}

void arcade::Console::previousLib(std::string &index)
{
	size_t count = 1;

	auto lib = this->graphics.begin();
	for (; lib != this->graphics.end() && index != lib->first; ++lib, ++count);
	if (lib->first == index && count > 1) {
		--lib;
		this->launchGraphics("launch", lib->second);
		std::cerr << std::endl;
		index = lib->first;
		std::cerr << std::endl;
	} else if (lib->first == index && count == 1) {
		lib = this->graphics.end();
		--lib;
		this->launchGraphics("launch", lib->second);
		std::cerr << std::endl;
		index = lib->first;
		std::cerr << std::endl;
	}
}

void arcade::Console::changeLib(std::unique_ptr<arcade::IGraphics> &graphics,
						  arcade::keys &key, std::string &index)
{
	std::string playerName = graphics->playerName;

	graphics->closeWindow();
	graphics.release();
	if (key == arcade::NEXT_LIB)
		this->nextLib(index);
	else
		this->previousLib(index);
	graphics.swap(this->graphics_ptr());
	if (graphics->type != arcade::libType::GRAPHICAL_LIB)
		throw (arcade::Exception("Console", "Invalid lib: " + index));
	graphics->openWindow();
	graphics->clearWindow();
	graphics->state = arcade::GAME;
	graphics->playerName = playerName;
}