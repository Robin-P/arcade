//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml class
//

#ifndef LIB_NCURSES_CLASS_HPP_
#define LIB_NCURSES_CLASS_HPP_

#include <algorithm>
#include <fstream>
#include <unistd.h>
#include <ncurses.h>
#include <curses.h>
#include <iostream>
#include <thread>
#include "IGraphics.hpp"
#include "exception.hpp"

namespace arcade {
	class Ncurses : public IGraphics {
	public:
		Ncurses();
		~Ncurses() override;
		void printCentipede();
		arcade::menuLeave menu(std::map<std::string, void *> &game_lib_name,
				 std::map<std::string, void *> &grapics_lib_name) override;
		void createBlocks(const std::string &game_name) override;
		bool exit() override;
		void closeWindow() override;
		void init_colors();
		void loadMap(const std::string &path_name, size_t i);
		void printMap();
		void printSnake();
		void printPacman();
		void selectSnake(int max, int nb_col, int nb_lin);
		void printStatus(std::map<std::string, void *>, std::map<std::string, void *>);
		void drawMap(std::vector<std::string> &map) override;
		arcade::keys getKey() override;
		void openWindow() override;
		void clearWindow() override;
		void displayWindow() override;
		void refreshWindow() override;
		bool isAlive() override;
		void actionKey(size_t i, size_t j);
		void cleanRessources();
		void playMusic(const std::string &index) override;
		void stopMusic(const std::string &index) override;
		static void playThis(const std::string &music);
		void createMusic(const std::string &index, const std::string &path) override;
		std::string my_substr(const std::string &str, const std::string &after,
				      const std::string &before);
		arcade::keys key;
		std::map<std::string, std::string> musics;
		std::vector<std::string> map;
		std::vector<std::string> snake;
		std::vector<std::string> r_snake;
		std::vector<std::string> pacman;
		std::vector<std::string> fantoms;
		std::vector<std::string> centipede;
		size_t choose;
	private:
		bool isOpen;
		bool isExit;
	};
}
#endif /* !LIB_NCURSES_CLASS_HPP_ */
