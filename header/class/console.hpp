//
// EPITECH PROJECT, 2018
// arcade
// File description:
// arcade
//

#ifndef CLASS_ARCADE_HPP_
#define CLASS_ARCADE_HPP_

#include <memory>
#include <map>
#include <vector>
#include "IGame.hpp"
#include "exception.hpp"

namespace arcade {
	class Console {
	public:
		Console();
		~Console();

		int help(int nb);
		void *openLib(const std::string &str);
		void setScore(std::string &game_lib_name, std::unique_ptr<arcade::IGraphics> &graphics,
			      const int &score);
		void launchGraphics(std::string entry_point, void *handle);
		void launchGame(std::string entry_point, void *handle);
		void menu(std::string index, std::string playerName);
		void loadGames();
		void loadGraphics();
		void nextLib(std::string &index);
		void previousLib(std::string &index);
		void changeLib(std::unique_ptr<arcade::IGraphics> &graphics, arcade::keys &key, std::string &index);
		void previousGame(std::string &index);
		void nextGame(std::string &index);
		void changeGame(std::unique_ptr<arcade::IGame> &game, arcade::keys &key, std::string &index);
		void startGame(std::unique_ptr<arcade::IGraphics> &graphics, arcade::menuLeave &result, std::string &graphicIndex, std::string &gameIndex);
	private:
		std::map<std::string, void *> games;
		std::map<std::string, void *> graphics;
		std::unique_ptr<arcade::IGraphics> &(*graphics_ptr)();
		std::unique_ptr<arcade::IGame> &(*game_ptr)();
	};
}
#endif /* !CLASS_ARCADE_HPP_ */
