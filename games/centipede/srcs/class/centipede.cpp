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
#include "centipede.hpp"

using u_centipede = arcade::Centipede;
using u_snake = arcade::Centipede::Snake;

u_centipede::Centipede() : name("centipede")
{
	this->type = arcade::libType::GAME_LIB;
	srand(time(nullptr));
	init_game();
}

const std::string &u_centipede::getName() const
{
	return this->name;
}

u_centipede::~Centipede()
{
}

u_snake::Snake()
{}

u_snake::~Snake()
{}

void u_snake::init_snake()
{
	s.push_back({1, 4});
	s.push_back({1, 3});
	s.push_back({1, 2});
	s.push_back({1, 1});
	this->t = RIGHT;
}

void u_centipede::init_snake(size_t i, size_t nb)
{
	std::unique_ptr<u_snake> new_snake = std::make_unique<u_snake>();

	if (i != list[nb]->s.size()) {
		while (i < list[nb]->s.size()) {
			new_snake->s.push_back({list[nb]->s[i].x, list[nb]->s[i].y});
			this->map[list[nb]->s[i].x][list[nb]->s[i].y] = '5';
			list[nb]->s.erase(list[nb]->s.begin() - 1 + i);
		}
		new_snake->t = list[nb]->t;
		this->list.push_back(std::move(new_snake));
	}
}

int u_centipede::Loadmap()
{
	std::ifstream file(MAPS_PATH + std::string("centipede") + MAPS_EXT);
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
		throw (arcade::Exception("centipede", "upload map failed."));
	return 0;
}

void u_centipede::setKey(const arcade::keys &skey)
{
	this->key = skey;
}

void u_centipede::init_game()
{
	std::unique_ptr<u_snake> new_snake = std::make_unique<u_snake>();

	this->last = arcade::NONE;
	this->key = arcade::NONE;
	this->max_x = 0;
	this->max_y = 0;
	this->prevLoop = std::chrono::system_clock::now();
	this->snakeLoop = std::chrono::system_clock::now();
	this->nb_eat = 1;
	this->Loadmap();
	new_snake->init_snake();
	this->list.clear();
	this->list.push_back(std::move(new_snake));
	player_x = max_x - 3;
	player_y = max_y / 2;
}

void u_centipede::move_player()
{
	this->map[player_x][player_y] = ' ';
	if (this->key == arcade::RIGHT && player_y + 1 < max_y - 1)
		player_y += 1;
	else if (this->key == arcade::LEFT && player_y - 1 > 0)
		player_y -= 1;
	else if (this->key == arcade::UP && player_x - 1 >= (max_x - 3) * 0.8)
		player_x -= 1;
	else if (this->key == arcade::DOWN && player_x + 1 <= max_x - 3)
		player_x += 1;
	this->map[player_x][player_y] = 'A';
}

void u_centipede::check_missile()
{
	for (size_t i = 1; i < max_x - 3; ++i) {
		for (size_t j = 1; j < max_y - 1; ++j)
			if (this->map[i][j] == 'o') {
				this->map[i][j] = ' ';
				if (i > 1 && this->map[i - 1][j] <= '5' &&
					this->map[i - 1][j] >= '1')
					this->map[i - 1][j] -= 1;
				else if (this->map[i - 1][j] == '0')
					this->map[i - 1][j] = ' ';
				else if (i > 1)
					this->map[i - 1][j] = 'o';
			}
	}
}

void u_centipede::create_new_snake()
{
	std::unique_ptr<u_snake> new_snake = std::make_unique<u_snake>();

	this->nb_eat += 1;
	if (this->nb_eat == 10)
		return;
	new_snake->init_snake();
	this->list.push_back(std::move(new_snake));
}

void u_centipede::check_road(size_t nb)
{
	if (list[nb]->t == u_snake::RIGHT &&
		((map[list[nb]->s[0].x][list[nb]->s[0].y + 1] == ' ') ||
		 (map[list[nb]->s[0].x][list[nb]->s[0].y + 1] == 'o') ||
		 (map[list[nb]->s[0].x][list[nb]->s[0].y + 1] == 'A')))
		list[nb]->s[0].y += 1;
	else if (list[nb]->t == u_snake::LEFT &&
			 ((map[list[nb]->s[0].x][list[nb]->s[0].y - 1] == ' ') ||
			  (map[list[nb]->s[0].x][list[nb]->s[0].y - 1] == 'o') ||
			  (map[list[nb]->s[0].x][list[nb]->s[0].y - 1] == 'A')))
		list[nb]->s[0].y -= 1;
	else {
		for (int i = 0; map[list[nb]->s[0].x + 1][list[nb]->s[0].y] <= '5' &&
						map[list[nb]->s[0].x + 1][list[nb]->s[0].y] >=
						'0'; ++i)
			list[nb]->s[0].x += 1;
		list[nb]->t == u_snake::LEFT ? list[nb]->t = u_snake::RIGHT
									 : list[nb]->t = u_snake::LEFT;
		if (static_cast<size_t>(list[nb]->s[0].x) < max_x - 3)
			list[nb]->s[0].x += 1;
		else {
			map[list[nb]->s[0].x][list[nb]->s[0].y] = ' ';
			list[nb]->s.erase(list[nb]->s.begin());
			if (list[nb]->s.empty()) {
				list.erase(list.begin() - 1);
				this->nb_eat -= 1;
				create_new_snake();
			}
		}
	}
}

char u_centipede::getChar(size_t nb, size_t i)
{
	if (list[nb]->s.size() > 1 && list[nb]->s[i].y < list[nb]->s[i + 1].y)
		return 'H';
	else if (list[nb]->s.size() > 1 && list[nb]->s[i].y > list[nb]->s[i + 1].y)
		return 'F';
	else
		return 'G';
}

void u_centipede::move_snake(size_t nb)
{
	this->map[list[nb]->s[list[nb]->s.size() - 1].x][list[nb]->s[
			list[nb]->s.size() - 1].y] = ' ';
	for (size_t i = list[nb]->s.size() - 1; i > 0; --i) {
		list[nb]->s[i] = list[nb]->s[i - 1];
		if (this->map[list[nb]->s[i].x][list[nb]->s[i].y] == 'o') {
			init_snake(i, nb);
			return;
		}
	}
	check_road(nb);
	char c = getChar(nb, 0);
	switch (this->map[list[nb]->s[0].x][list[nb]->s[0].y]) {
		case 'o':
			this->map[list[nb]->s[0].x][list[nb]->s[0].y] = '5';
			list[nb]->s.erase(list[nb]->s.begin());
			if (list[nb]->s.empty()) {
				list.erase(list.begin() + nb);
				create_new_snake();
			}
		default:
			this->map[list[nb]->s[0].x][list[nb]->s[0].y] = c;
	}
}

void u_centipede::change_map(std::unique_ptr<arcade::IGraphics> &graphics)
{
	auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now() - this->prevLoop).count();
	if (tmp > 100) {
		check_missile();
		move_player();
		if (this->key == arcade::SHOOT) {
			if (this->map[player_x - 1][player_y] >= '1' &&
				this->map[player_x - 1][player_y] <= '5')
				this->map[player_x - 1][player_y] -= 1;
			else if (this->map[player_x - 1][player_y] == '0')
				this->map[player_x - 1][player_y] = ' ';
			else
				this->map[player_x - 1][player_y] = 'o';
		}
		this->prevLoop = std::chrono::system_clock::now();
		for (size_t i = 0; i < list.size(); ++i)
			move_snake(i);
		if (map[player_x][player_y] != 'A')
			graphics->state = arcade::MENU;
		return;
	}
	auto sna = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now() - this->snakeLoop).count();
	if (sna > 20000) {
		this->snakeLoop = std::chrono::system_clock::now();
		create_new_snake();
	}
	graphics->state = arcade::GAME;
}

int u_centipede::start(std::unique_ptr<arcade::IGraphics> &graphics)
{
	this->key = (this->key == arcade::NONE ? this->last : this->key);
	this->last = this->key;
	graphics->clearWindow();
	if (this->key == arcade::RESET) {
		this->init_game();
		return start(graphics);
	} else
		this->change_map(graphics);
	if (this->nb_eat > 20)
		graphics->state = arcade::MENU;
	graphics->drawMap(this->map);
	this->key = arcade::NONE;
	return static_cast<int>(this->nb_eat);
}
