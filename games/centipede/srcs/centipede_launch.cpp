//
// EPITECH PROJECT, 2018
// arcade
// File description:
// game sfml
//

#include <memory>
#include "centipede.hpp"

extern "C" {
	std::unique_ptr<arcade::IGame> launch()
	{
		return std::make_unique<arcade::Centipede>();
	}
}
