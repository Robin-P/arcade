//
// EPITECH PROJECT, 2018
// arcade
// File description:
// game sfml
//

#include <memory>
#include "sfml.hpp"

extern "C" {
	std::unique_ptr<arcade::IGraphics> launch()
	{
		return std::make_unique<arcade::Sfml>();
	}
}
