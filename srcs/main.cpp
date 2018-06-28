/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** main
*/

#include <cstdio>
#include "console.hpp"

int main(int ac, char **av)
{
	arcade::Console console;

	if (ac == 1 || av[1] == nullptr)
		return console.help(84);
	try {
		std::string first = av[1];

		if (first.substr(0, 2) != "./")
			first = "./" + first;
		console.loadGraphics();
		console.loadGames();
		console.menu(first, "");
	} catch (arcade::Exception &e) {
		std::cout << e.what() << std::endl;
		return 84;
	}
	return 0;
}
