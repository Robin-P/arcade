//
// EPITECH PROJECT, 2018
// ghodt
// File description:
// ghost
//

#ifndef GHOST_HPP_
#define GHOST_HPP_

#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
#include <string>
#include "exception.hpp"
#include "IGame.hpp"
#include "IGraphics.hpp"

namespace arcade {
	class Ghost {
	public:
		Ghost(int x, int y, char _id);
		~Ghost();
		bool validMove(const char &aCase);
		int move(std::vector<std::string> &map);
		int moveHome(std::vector<std::string> &map);
		/* order */
		void setOrder(position order);
		/* STATIC */
		static void addGhost(std::vector<std::unique_ptr<arcade::Ghost>> &array, std::vector<std::string> &map);
		static void createGhost(std::vector<std::unique_ptr<arcade::Ghost>> &array, int nb, const char &firstId);
		position pacman;
	private:
		//std::vector<std::string> map;
		position order;
		char id;
		position pos;
		char last;
		enum pacmanState {INVINSIBLE, HITABLE};
		pacmanState mod;
		std::chrono::time_point<std::chrono::system_clock> prevLoop;
	};
}

#endif /* GHOST_HPP_ */
