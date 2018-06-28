//
// EPITECH PROJECT, 2018
// arcade
// File description:
// interface
//

#ifndef IGAMEMODULE_HPP_
#define IGAMEMODULE_HPP_

# include <memory>
# include <iostream>
# include "IGraphics.hpp"

namespace arcade {
	typedef struct position {
		int x;
		int y;
	} position;
	class IGame {
	public:
		virtual ~IGame() = default;
		virtual void setKey(const arcade::keys &key) = 0;
		virtual int start(std::unique_ptr<IGraphics> &graphics) = 0;
		virtual const std::string &getName() const = 0;
		arcade::libType type;
	};
}

#endif /* !IGAMEMODULE_HPP_ */
