//
// EPITECH PROJECT, 2018
// arcade
// File description:
// console
//

#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#include "console.hpp"
#include "tools.hpp"

using u_console = arcade::Console;

u_console::Console()
{
	this->graphics_ptr = nullptr;
	this->game_ptr = nullptr;
}

u_console::~Console()
{
	for (auto game = this->games.begin(); game != games.end(); ++game) {
		if (game->second)
			if (dlclose(game->second) == 0)
				std::cout << game->first << " close" << std::endl;
	}
	for (auto lib = this->graphics.begin(); lib != graphics.end(); ++lib) {
		if (lib->second)
			if (dlclose(lib->second) == 0)
				std::cout << lib->first << " close" << std::endl;
	}
	this->graphics.clear();
	this->games.clear();
}

int u_console::help(int nb)
{
	std::cout << "./arcade \'Lib_Path_Name.so\'" << std::endl;
	return nb;
}

void *u_console::openLib(const std::string &path)
{
	void *new_handle = dlopen(path.c_str(), RTLD_LAZY);

	if (!new_handle) {
		std::cout << dlerror() << std::endl;
		throw arcade::Exception("Console",
								"lib: \'" + path + "\' can\'t be opened.");
	}
	std::cerr << path << " open" << std::endl;
	return new_handle;
}

void u_console::launchGraphics(std::string entry, void *handle)
{
	void *ptr = nullptr;

	if (!handle) {
		this->graphics.clear();
		throw arcade::Exception("Console", "Graphics lib handle is null");
	}
	ptr = dlsym(handle, entry.c_str());
	if (!ptr)
		throw arcade::Exception("Console",
								"Graphics lib entry point \'" + entry +
								"\' not found");
	this->graphics_ptr = reinterpret_cast<std::unique_ptr<arcade::IGraphics> &(*)()>(ptr);
}


void u_console::launchGame(std::string entry_point, void *handle)
{
	void *ptr = nullptr;

	if (!handle) {
		this->games.clear();
		throw arcade::Exception("Console", "Game lib handle is null");
	}
	ptr = dlsym(handle, entry_point.c_str());
	if (!ptr)
		throw arcade::Exception("Console",
								"Game lib entry point \'" + entry_point +
								"\' not found");
	this->game_ptr = reinterpret_cast<std::unique_ptr<arcade::IGame> &(*)()>(ptr);
}

void u_console::loadGames()
{
	std::string libName = LIB_NAME;
	std::string libExt = GAMES_LIB_EXT;
	dirent *de;
	DIR *dp;

	dp = opendir(GAME_DIR);
	if (dp) {
		while (true) {
			de = readdir(dp);
			if (de == nullptr)
				break;
			std::string str(de->d_name);
			if (str.substr(0, libName.size()) == LIB_NAME &&
				str.substr(str.size() - libExt.size(), libExt.size()) ==
				GAMES_LIB_EXT) {
				this->games[GAME_DIR + str] = openLib(GAME_DIR + str);
			}
		}
		closedir(dp);
	}
}

void u_console::loadGraphics()
{
	std::string libName = LIB_NAME;
	std::string libExt = GRAPHICS_LIB_EXT;
	dirent *de;
	DIR *dp;

	dp = opendir(LIB_DIR);
	if (dp) {
		while (true) {
			de = readdir(dp);
			if (de == nullptr)
				break;
			std::string str(de->d_name);
			if (str.substr(0, libName.size()) == LIB_NAME &&
				str.substr(str.size() - libExt.size(), libExt.size()) ==
				GRAPHICS_LIB_EXT) {
				this->graphics[LIB_DIR + str] = openLib(LIB_DIR + str);
			}
		}
		closedir(dp);
	}
}

void u_console::startGame(std::unique_ptr<arcade::IGraphics> &graphics,
						  arcade::menuLeave &result, std::string &index, std::string &gameIndex)
{
	int score;
	arcade::keys key;

	gameIndex = result.path;
	this->launchGame("launch", this->games[result.path]);
	std::unique_ptr<arcade::IGame> &game = this->game_ptr();
	if (!game)
		throw (arcade::Exception("Console", "Game lib return null"));
	if (game->type != arcade::libType::GAME_LIB)
		throw (arcade::Exception("Console", "Invalid lib: " + result.path));
	graphics->clearWindow();
	graphics->state = arcade::GAME;
	graphics->createBlocks(game->getName());
	while (graphics->isAlive() && graphics->state == arcade::GAME) {
		key = graphics->getKey();
		game->setKey(key);
		if (key == arcade::ESC) {
			break;
		} else if (this->graphics.size() > 1 &&
				 (key == arcade::NEXT_LIB || key == arcade::PREVIOUS_LIB)) {
			graphics->stopMusic("main");
			this->changeLib(graphics, key, index);
			graphics->createBlocks(game->getName());
			graphics->createMusic("main", MUSIC_PATH + std::string("main.ogg"));
			graphics->playMusic("main");
		} else if (this->games.size() > 1 &&
				  (key == arcade::NEXT_GAME || key == arcade::PREVIOUS_GAME)) {
			this->changeGame(game, key, gameIndex);
			graphics->createBlocks(game->getName());
		} else if (key != arcade::PAUSE)
			score = game->start(graphics);
	}
	graphics->state = arcade::MENU;
	this->setScore(result.path, graphics, score);
}

void u_console::menu(std::string index_graphics, std::string playerName)
{
	std::string gameIndex;
	this->launchGraphics("launch", this->graphics[index_graphics]);
	std::unique_ptr<arcade::IGraphics> &libGraphic = this->graphics_ptr();

	if (!libGraphic)
		throw (arcade::Exception("Console", "Graphics lib return null"));
	if (libGraphic->type != arcade::libType::GRAPHICAL_LIB)
		throw (arcade::Exception("Console", "Invalid lib: " + index_graphics));
	libGraphic->playerName = playerName;
	libGraphic->createMusic("main", MUSIC_PATH + std::string("main.ogg"));
	libGraphic->playMusic("main");
	while (!libGraphic->exit()) {
		libGraphic->openWindow();
		libGraphic->clearWindow();
		arcade::menuLeave result = libGraphic->menu(this->games, this->graphics);
		if (result.state == arcade::menuLeave::GRAPHIC) {
			for (size_t index = 0; index < this->graphics.size(); ++index)
				if (this->graphics[result.path]) {
					libGraphic->closeWindow();
					libGraphic->stopMusic("main");
					return this->menu(result.path, libGraphic->playerName);
				}
		} else if (result.state == arcade::menuLeave::GAME)
			this->startGame(libGraphic, result, index_graphics, gameIndex);
		else
			break;
	}
	libGraphic->closeWindow();
}
