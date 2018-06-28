//
// EPITECH PROJECT, 2018
// mdr
// File description:
// mdr
//

#ifndef CENTIPEDE_H_
#define CENTIPEDE_H_

#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
#include "exception.hpp"
#include "IGame.hpp"
#include "IGraphics.hpp"

namespace arcade {
	class Centipede : public IGame {
	public:
		class Snake {
		public:
			Snake();
			~Snake();
			std::vector<position> s;
			enum k{
				LEFT,
				RIGHT,
			};
			k t;
			void init_snake();
		};
		Centipede();
		~Centipede() override;
		int start(std::unique_ptr<arcade::IGraphics> &Graphics) override;

		int Loadmap();
		void init_game();
		void setKey(const arcade::keys &key) override;
		void change_map(std::unique_ptr<arcade::IGraphics> &Graphics);
		void move_player();
		void check_missile();
		void move_snake(size_t nb);
		void init_snake(size_t i, size_t nb);
		void create_new_snake();
		void check_road(size_t nb);
		char getChar(size_t nb, size_t i);
		const std::string &getName() const override;
	private:
		std::string name;
		std::vector<std::string> map;
		std::chrono::time_point<std::chrono::system_clock> prevLoop;
		std::chrono::time_point<std::chrono::system_clock> snakeLoop;
		arcade::keys key;
		arcade::keys last;
		size_t max_x;
		size_t max_y;
		size_t player_x;
		size_t player_y;
		std::vector<std::unique_ptr<Snake>> list;
		size_t nb_eat;
	};
}
#endif /* CENTIPEDE_H_ */
