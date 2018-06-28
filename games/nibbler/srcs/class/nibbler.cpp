//
// EPITECH PROJECT, 2018
// mdr
// File description:
// mdr
//

#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <algorithm>
#include "nibbler.hpp"

using u_nibbler = arcade::Nibbler;

u_nibbler::Nibbler() : name("nibbler")
{
	this->type = arcade::libType::GAME_LIB;
	srand(time(nullptr));
	this->init_game();
}

u_nibbler::~Nibbler()
{
}

const std::string &u_nibbler::getName() const
{
	return this->name;
}

int u_nibbler::Loadmap()
{
	std::ifstream file(MAPS_PATH + std::string("nibbler") + MAPS_EXT);
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
		throw (arcade::Exception("nibbler", "upload map failed."));
	return 0;
}

void u_nibbler::add_nibbler()
{
	++this->nb_eat;
	this->s.push_back(this->s[this->s.size() - 1]);
}

int u_nibbler::modify_map()
{
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now() - this->prevLoop).count();
	if (tmp > 100) {
		this->prevLoop = std::chrono::system_clock::now();
		for (auto j = static_cast<int>(this->s.size() - 1); j > 0; --j) {
			this->map[this->s[j].x][this->s[j].y] = ' ';
			this->s[j] = this->s[j - 1];
		}
		if ((this->key == arcade::RIGHT &&
			 this->map[s[0].x][s[0].y + 1] != '#'))
			this->s[0].y += 1;
		else if (this->key == arcade::LEFT &&
				 this->map[s[0].x][s[0].y - 1] != '#')
			--this->s[0].y;
		else if (this->key == arcade::UP &&
				 this->map[s[0].x - 1][s[0].y] != '#')
			--this->s[0].x;
		else if (this->key == arcade::DOWN &&
				 this->map[s[0].x + 1][s[0].y] != '#')
			++this->s[0].x;
	}
	return 0;
}

char u_nibbler::getFirstChar()
{
	if (this->key == arcade::UP)
		return ('A');
	else if (this->key == arcade::RIGHT)
		return ('B');
	else if (this->key == arcade::DOWN)
		return ('C');
	else if (this->key == arcade::LEFT)
		return ('D');
	return ('A');
}

char u_nibbler::getChar(size_t i)
{
	size_t nb = (i % 3) * 4;

	if (this->s[i].x > this->s[i - 1].x)
		return static_cast<char>('E' + nb);
	else if (this->s[i].y < this->s[i - 1].y)
		return static_cast<char>('F' + nb);
	else if (this->s[i].x < this->s[i - 1].x)
		return static_cast<char>('G' + nb);
	else if (this->s[i].y > this->s[i - 1].y)
		return static_cast<char>('H' + nb);
	return ('G');
}

int u_nibbler::change_map()
{
	size_t j = this->s.size();
	for (size_t i = 0; i < j; ++i) {
		if (this->map[this->s[i].x][this->s[i].y] == 'o') {
			add_nibbler();
		}
		i == 0 ? this->map[this->s[i].x][this->s[i].y] = getFirstChar()
			   : this->map[this->s[i].x][this->s[i].y] = getChar(i);
	}

	if ((key == arcade::RIGHT && map[s[0].x][s[0].y] >= 'E' &&
		 map[s[0].x][s[0].y] <= 'P') ||
		(key == arcade::LEFT && map[s[0].x][s[0].y] >= 'E' &&
		 map[s[0].x][s[0].y] <= 'P') ||
		(key == arcade::DOWN && map[s[0].x][s[0].y] >= 'E' &&
		 map[s[0].x][s[0].y] <= 'P') ||
		(key == arcade::UP && map[s[0].x][s[0].y] >= 'E' &&
		 map[s[0].x][s[0].y] <= 'P'))
		return 1;
	return (modify_map() == 1 ? 1 : 0);
}

void u_nibbler::to_eat()
{
	for (auto &i : map)
		this->max_eat += std::count(i.begin(), i.end(), 'o');
}

void u_nibbler::init_game()
{
	this->s.clear();
	this->s.push_back({11, 15});
	this->s.push_back({11, 14});
	this->s.push_back({11, 13});
	this->s.push_back({11, 12});
	this->nb_eat = 0;
	this->max_eat = 0;
	this->max_x = 0;
	this->max_y = 0;
	this->prevLoop = std::chrono::system_clock::now();
	this->Loadmap();
	this->to_eat();
	this->last = arcade::RIGHT;
	this->key = arcade::NONE;
}

void u_nibbler::setKey(const arcade::keys &skey)
{
	this->key = skey;
}

int u_nibbler::start(std::unique_ptr<arcade::IGraphics> &graphics)
{
	int res = 0;

	this->key = ((this->key == arcade::SHOOT || this->key == arcade::NONE) ? this->last : this->key);
	this->last = this->key;
	if (std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now() - this->prevLoop).count() > 1) {
		graphics->clearWindow();
		graphics->drawMap(this->map);
	}
	if (this->key == arcade::RESET) {
		this->init_game();
		return start(graphics);
	} else
		res = this->change_map();
	if (res != 0 || (this->nb_eat >= this->max_eat))
		graphics->state = arcade::MENU;
	this->key = arcade::NONE;
	return static_cast<int>(this->nb_eat);
}
