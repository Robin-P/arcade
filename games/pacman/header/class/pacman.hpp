/*
** EPITECH PROJECT, 2018
** pacman
** File description:
** pacman
*/

#ifndef PACMAN_H_
#define PACMAN_H_

#include <vector>
#include <iostream>
#include <time.h>
#include <ctime>
#include <chrono>
#include <string>
#include "exception.hpp"
#include "IGame.hpp"
#include "IGraphics.hpp"
#include "ghost.hpp"

namespace arcade {
	class Pacman : public IGame {
	public:
		Pacman();
		~Pacman() override;

		bool pause();
		int load_map();
		void setKey(const arcade::keys &key) override;
		int move_ghost(std::vector<std::unique_ptr<arcade::Ghost>> &array, std::vector<std::string> &map);
		int moveHome_ghost(std::vector<std::unique_ptr<arcade::Ghost>> &array, std::vector<std::string> &map);
		int modify_map(std::unique_ptr<arcade::IGraphics> &);
		char getFirstChar();
		int change_map(std::unique_ptr<arcade::IGraphics> &);
		int check_map();
		int check_death();
		void init_game();
		void check_pacgum();
		int start(std::unique_ptr<arcade::IGraphics> &graphics) override;
		const std::string &getName() const override;
	protected:
		std::string name;
		std::vector<std::unique_ptr<arcade::Ghost>> ghosts;
		std::vector<std::string> map;
		std::chrono::time_point<std::chrono::system_clock> prevLoop;
		std::chrono::time_point<std::chrono::system_clock> Godlike;
		arcade::keys last;
		arcade::keys key;
		enum pacmanState {HITABLE, INVINSIBLE};
		int x;
		int y;
		int ant_x;
		int ant_y;
		pacmanState mod;
		size_t nb_eat;
		size_t max_x;
		size_t max_y;
	};
}

#endif /* PACMAN_H_ */
