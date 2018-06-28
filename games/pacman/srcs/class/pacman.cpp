//
// EPITECH PROJECT, 2018
// pacman
// File description:
// pacman
//

#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <unistd.h>
#include <algorithm>
#include "pacman.hpp"

using u_pacman = arcade::Pacman;

u_pacman::Pacman() : name("pacman")
{
	this->type = arcade::libType::GAME_LIB;
	srand(time(nullptr));
	this->init_game();
}

u_pacman::~Pacman()
{
}

const std::string &u_pacman::getName() const
{
	return this->name;
}

void u_pacman::init_game()
{
	this->key = arcade::NONE;
	this->last = arcade::RIGHT;
	this->mod = HITABLE;
	this->x = 16;
	this->y = 22;
	this->ant_x = 0;
	this->ant_y = 0;
	this->max_x = 0;
	this->max_y = 0;
	this->nb_eat = 0;
	this->prevLoop = std::chrono::system_clock::now();
	this->load_map();
	this->ghosts.clear();
	arcade::Ghost::createGhost(this->ghosts, 3, 'E');
	arcade::Ghost::addGhost(this->ghosts, this->map);
}

void u_pacman::setKey(const arcade::keys &skey)
{
	this->key = skey;
}

int u_pacman::load_map()
{
	std::ifstream file(MAPS_PATH + std::string("pacman") + MAPS_EXT);
	std::string str;

	this->map.clear();
	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, str);
			if (this->max_y == 0)
				this->max_y = str.size();
			this->map.push_back(str);
			++max_x;
		}
	} else
		throw (arcade::Exception("pacman", "upload map failed"));
	return 0;
}

char u_pacman::getFirstChar()
{
	if (this->key == arcade::UP)
		return 'A';
	else if (this->key == arcade::RIGHT)
		return 'B';
	else if (this->key == arcade::DOWN)
		return 'C';
	else if (this->key == arcade::LEFT)
		return 'D';
	return 'A';
}

bool u_pacman::pause()
{
	if (this->key != arcade::PAUSE)
		return false;
	usleep(10000);
	return true;
}

int u_pacman::move_ghost(std::vector<std::unique_ptr<arcade::Ghost>> &array,
						 std::vector<std::string> &map)
{
	for (auto &ghost : array) {
		ghost->pacman = {this->x, this->y};
		if ((ghost->move(map)) != 0)
			return 1;
	}
	return 0;
}

int u_pacman::moveHome_ghost(std::vector<std::unique_ptr<arcade::Ghost>> &array,
			 std::vector<std::string> &map)
{
        for (auto &ghost : array) {
		ghost->pacman = {this->x, this->y};
		if ((ghost->moveHome(map)) != 0)
			return 1;
	}
        return 0;
}

void u_pacman::check_pacgum()
{
	if (this->mod == INVINSIBLE) {
		auto timer = std::chrono::duration_cast<std::chrono::milliseconds> (std::chrono::system_clock::now() - Godlike).count();

		if (timer > 8000) {
			this->mod = HITABLE;
			/* Ici pour le changement d'état du fantome*/
		}
	}
	else if (this->map[this->x][this->y] == 'b') {
		this->mod = INVINSIBLE;
		/* Ici pour le changement d'état du fantome*/
		this->Godlike = std::chrono::system_clock::now();
	}
}

int u_pacman::modify_map(std::unique_ptr<arcade::IGraphics> &graphics)
{
	graphics->clearWindow();
	arcade::Ghost::addGhost(this->ghosts, this->map);
	if (this->mod == INVINSIBLE) {
		this->moveHome_ghost(this->ghosts, this->map);
	} else if (((move_ghost(this->ghosts, this->map) != 0) ||
		    (key == arcade::RIGHT &&
		     (this->map[x][y + 1] >= 'E' && this->map[x][y + 1] <= 'Z')) ||
		    (key == arcade::LEFT &&
		     (this->map[x][y - 1] >= 'E' && this->map[x][y - 1] <= 'Z')) ||
		    (key == arcade::DOWN &&
		     (this->map[x - 1][y] >= 'E' && this->map[x - 1][y] <= 'Z')) ||
		    (key == arcade::UP &&
		     (this->map[x + 1][y] >= 'E' && this->map[x + 1][y] <= 'Z')) ||
		    (this->map[x][y] >= 'E' && this->map[x][y] <= 'Z')))
		return 1;

	this->prevLoop = std::chrono::system_clock::now();
	this->ant_x = this->x;
	this->ant_y = this->y;
	this->map[this->x][this->y] = ' ';
	if ((this->key == arcade::RIGHT && this->map[x][y + 1] != '#'))
		this->y = this->y + 1;
	else if ((this->key == arcade::LEFT && this->map[x][y - 1] != '#'))
		this->y = this->y - 1;
	else if ((this->key == arcade::UP && this->map[x - 1][y] != '#'))
		this->x = this->x - 1;
	else if ((this->key == arcade::DOWN && this->map[x + 1][y] != '#'))
		this->x = this->x + 1;
	else if (this->key == arcade::RESET) {
		this->init_game();
		return start(graphics);
	}
	if (this->map[this->x][this->y] == 'b' ||
	    this->map[this->x][this->y] == 'o')
		++this->nb_eat;
	check_pacgum();
	this->map[this->x][this->y] = getFirstChar();
	this->prevLoop = std::chrono::system_clock::now();
	return 0;
}

int u_pacman::change_map(std::unique_ptr<arcade::IGraphics> &graphics)
{
	int res = 0;

	if ((std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now() - this->prevLoop).count()) >=
		100)
		res = modify_map(graphics);
	graphics->drawMap(this->map);
	return (res);
}

int u_pacman::check_map()
{
	int b = 2;

	for (int a = 0 ; this->map[a][0] ; ++a) {
		if (this->map[a].find('o') != std::string::npos) {
			b = 1;
			if (this->map[a].find('b') != std::string::npos)
				b = 0;
		}
	}
	if (b == 2)
		return (1);
	return (0);
}

int u_pacman::check_death()
{
	if (this->map[this->x][this->y] >= 'E' &&
		this->map[this->x][this->y] <= 'Z')
		return (1);
	return (0);
}

int u_pacman::start(std::unique_ptr<arcade::IGraphics> &graphics)
{
	this->key = ((this->key == arcade::SHOOT || this->key == arcade::NONE) ? this->last : this->key);
	this->last = this->key;
	if (check_map() != 0 && check_death() != 0) {
		graphics->state = arcade::MENU;
		return static_cast<int>(this->nb_eat);
	}
	if (this->change_map(graphics) != 0)
		graphics->state = arcade::MENU;
	return static_cast<int>(this->nb_eat);
}
