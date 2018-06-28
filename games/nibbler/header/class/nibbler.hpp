//
// EPITECH PROJECT, 2018
// mdr
// File description:
// mdr
//

#ifndef NIBBLER_H_
#define NIBBLER_H_

#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
#include "exception.hpp"
#include "IGame.hpp"
#include "IGraphics.hpp"

namespace arcade {
	class Nibbler : public IGame {
	public:
		Nibbler();
		~Nibbler() override;
		int start(std::unique_ptr<arcade::IGraphics> &Graphics) override;

		int Loadmap();
		void setKey(const arcade::keys &key) override;
		int change_map();
		int modify_map();
		void add_nibbler();
		char getFirstChar();
		char getChar(size_t i);
		void to_eat();
		void init_game();
		const std::string &getName() const override;
	private:
		std::string name;
		std::vector<std::string> map;
		std::vector<position> s;
		std::chrono::time_point<std::chrono::system_clock> prevLoop;
		arcade::keys last;
		arcade::keys key;
		size_t max_eat;
		size_t nb_eat;
		size_t max_x;
		size_t max_y;
	};
}
#endif /* NIBBLER_H_ */
