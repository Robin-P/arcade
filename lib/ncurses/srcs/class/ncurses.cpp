//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml class
//

#include "ncurses.hpp"

using u_ncurses = arcade::Ncurses;

u_ncurses::Ncurses()
{
	this->type = arcade::libType::GRAPHICAL_LIB;
	this->choose = 0;
	this->isExit = false;
	this->isOpen = false;
	this->key = arcade::NONE;
}

u_ncurses::~Ncurses()
{
}

std::string
u_ncurses::my_substr(const std::string &str, const std::string &after,
					 const std::string &extension)
{
	std::string result = str;

	result = result.substr(result.find(after) + after.size());
	result = result.substr(0, result.size() - extension.size());
	return result;
}

void u_ncurses::init_colors()
{
	init_pair(0, COLOR_BLACK, COLOR_BLACK);
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
	init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(4, COLOR_BLUE, COLOR_BLUE);
	init_pair(5, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(6, COLOR_CYAN, COLOR_CYAN);
	init_pair(7, COLOR_WHITE, COLOR_WHITE);
	init_pair(8, COLOR_BLUE, COLOR_BLUE);
	init_pair(9, COLOR_GREEN, COLOR_BLACK);
	init_pair(10, COLOR_CYAN, COLOR_BLACK);
	init_pair(11, COLOR_RED, COLOR_BLACK);
	init_pair(12, COLOR_BLUE, COLOR_BLACK);
	init_pair(13, COLOR_WHITE, COLOR_BLACK);
	init_pair(14, COLOR_YELLOW, COLOR_BLACK);
}

void u_ncurses::loadMap(const std::string &path_name, size_t i)
{
	std::ifstream file(path_name);
	std::string str;

	if (file.is_open())
		while (!file.eof()) {
			getline(file, str);
			switch (i) {
				case 1:
					this->map.push_back(str);
					break;
				case 2:
					this->snake.push_back(str);
					break;
				case 3:
					this->r_snake.push_back(str);
					break;
				case 4:
					this->pacman.push_back(str);
					break;
				case 5:
					this->fantoms.push_back(str);
					break;
				case 6:
					this->centipede.push_back(str);
					break;
			}
		}
}

void u_ncurses::printMap()
{
	WINDOW *boite = subwin(stdscr, 3, 22, LINES / 3 + 1, COLS / 2 - 11);
	size_t j = this->map.size();
	int y = map[0].size();
	static int color = 1;

	for (size_t i = 0; i < j; ++i) {
		for (size_t c = 0; c < map[i].size(); ++c) {
			if (this->map[i][c] != ' ') {
				attron(COLOR_PAIR(color));
				mvprintw(LINES / 4 - (map.size() / 2) + i,
						 COLS / 2 - (y / 2) + c, "#");
				attroff(COLOR_PAIR(color));
			}
			++color;
			if (color == 9)
				color = 1;
		}
	}
	box(boite, ACS_VLINE, ACS_HLINE);
	mvprintw(LINES / 3 + 2, COLS / 2 - this->playerName.size() / 2,
			 static_cast<const char *>(this->playerName.c_str()));
	attron(COLOR_PAIR(color + 8));
	mvprintw(LINES / 3, COLS / 2 - 3, "PSEUDO:");
	attroff(COLOR_PAIR(color + 8));
}

void u_ncurses::printSnake()
{
	size_t j = this->snake.size();
	int y = snake[0].size() + 1;
	static int color = 10;

	for (size_t i = 0; i < j; ++i) {
		attron(COLOR_PAIR(color));
		mvprintw(LINES - snake.size() - 1 + i, 1,
				 static_cast<const char *>(this->snake[i].c_str()));
		mvprintw(LINES - snake.size() - 1 + i, COLS - y,
				 static_cast<const char *>(this->r_snake[i].c_str()));
		attroff(COLOR_PAIR(color));
		++color;
		if (color == 15)
			color = 10;
	}
}

void u_ncurses::printCentipede()
{
	size_t j = this->centipede.size();
	int z = static_cast<int>(centipede[2].size() + 1);
	static int color = 10;

	for (size_t i = 0; i < j; ++i) {
		attron(COLOR_PAIR(color));
		mvprintw(LINES - centipede.size() - 1 + i, COLS / 2 - z / 2,
				 (this->centipede[i].c_str()));
		attroff(COLOR_PAIR(color));
		++color;
		if (color == 15)
			color = 10;
	}
}

void u_ncurses::printPacman()
{
	size_t j = this->fantoms.size();
	int y = static_cast<int>(fantoms[0].size() + 1);
	int z = static_cast<int>(pacman[0].size() + 1);
	static int color = 9;

	for (size_t i = 0; i < j; ++i) {
		attron(COLOR_PAIR(color));
		mvprintw(LINES - fantoms.size() - 1 + i, COLS / 2 - y / 2,
				 (this->fantoms[i].c_str()));
		attroff(COLOR_PAIR(color));
		attron(COLOR_PAIR(14));
		mvprintw(LINES - pacman.size() - 1 + i, COLS / 2 - z / 2,
				 (this->pacman[i].c_str()));
		attroff(COLOR_PAIR(14));
		++color;
		if (color == 15)
			color = 9;
	}
}

void u_ncurses::printStatus(std::map<std::string, void *> games,
							std::map<std::string, void *> libs)
{
	int nb = 0;
	auto gameIndex = games.begin();
	auto libIndex = libs.begin();

	size_t i = 0;
	for (; i < this->choose && gameIndex != games.end(); ++gameIndex, ++i);
	i = 0;
	for (; i < (this->choose - games.size()) &&
		   libIndex != libs.end(); ++libIndex, ++i);

	int index = 0;
	for (auto game = games.begin(); game != games.end(); ++game, ++index) {
		std::string game_name = my_substr(game->first, GAMES_LIB_PATH,
										  GAMES_LIB_EXT);
		std::transform(game_name.begin(), game_name.end(), game_name.begin(),
					   ::toupper);
		mvprintw(LINES / 2 - 2 + index * 2, COLS / 3 - game_name.size() / 2,
				 game_name.c_str());
		nb += 2;
	}
	index = 0;
	for (auto lib = libs.begin(); lib != libs.end(); ++lib, ++index) {
		std::string lib_name = my_substr(lib->first, GRAPHICS_LIB_PATH,
										 GRAPHICS_LIB_EXT);
		std::transform(lib_name.begin(), lib_name.end(), lib_name.begin(),
					   ::toupper);
		mvprintw(LINES / 2 - 2 + index * 2,
				 COLS - COLS / 3 - lib_name.size() / 2, lib_name.c_str());
		nb += 2;
	}
	mvprintw(LINES / 2 - 2 + libs.size() * 2, COLS - (COLS / 3) - 2, "EXIT");
	if (this->choose < games.size())
		nb = COLS / 3 - my_substr(gameIndex->first, GAMES_LIB_PATH,
								  GAMES_LIB_EXT).size() / 2;
	else if (this->choose < games.size() + libs.size())
		nb = COLS - COLS / 3 - my_substr(libIndex->first, GRAPHICS_LIB_PATH,
										 GRAPHICS_LIB_EXT).size() / 2;
	else
		nb = COLS - COLS / 3 - 2;
	if (this->choose < games.size()) {
		selectSnake(my_substr(gameIndex->first, GAMES_LIB_PATH,
							  GAMES_LIB_EXT).size(), nb,
					-1 + this->choose * 2);
		if (my_substr(gameIndex->first, GAMES_LIB_PATH, GAMES_LIB_EXT) ==
			"nibbler")
			printSnake();
		else if (my_substr(gameIndex->first, GAMES_LIB_PATH, GAMES_LIB_EXT) ==
				 "pacman")
			printPacman();
		else if (my_substr(gameIndex->first, GAMES_LIB_PATH, GAMES_LIB_EXT) ==
				 "centipede")
			printCentipede();
	}
		// else if (this->choose < game.size() + libs.size())
		//         selectSnake(my_substr(game[this->choose - game.size()], GAMES_LIB_PATH, GAMES_LIB_EXT).size(), nb, -1 + (this->choose - game.size())* 2);
	else
		selectSnake(6, nb, -1 + (this->choose - games.size()) * 2);
}

void u_ncurses::selectSnake(int max, int nb_col, int nb_lin)
{
	static int lin = -1;
	static int col = -1;
	static int lin2 = 1;
	static int col2 = max;
	static int color = 1;

	if (col > max || col2 > max) {
		lin = -1;
		col = -1;
		lin2 = 1;
		col2 = max;
	}
	attron(COLOR_PAIR(color));
	mvprintw(LINES / 2 - 1 + lin + nb_lin, nb_col + col, "#");
	mvprintw(LINES / 2 - 1 + lin2 + nb_lin, nb_col + col2, "#");
	attroff(COLOR_PAIR(color));
	if (col < max && lin != 1)
		++col;
	else if (col >= 0 && lin == 1) {
		--col;
	} else
		lin != 1 ? lin += 2 : lin -= 2;
	if (col2 < max && lin2 != 1)
		++col2;
	else if (col2 >= 0 && lin2 == 1) {
		--col2;
	} else
		lin2 != 1 ? lin2 += 2 : lin2 -= 2;
	++color;
	if (color == 9)
		color = 1;
}

void u_ncurses::actionKey(size_t i, size_t j)
{
	switch (this->key) {
		case arcade::LEFT :
			this->choose >= i - 1 ? this->choose = 0 : this->choose;
			break;
		case arcade::RIGHT :
			this->choose < i - 1 ? this->choose = i - 1 : this->choose;
			break;
		case arcade::UP :
			this->choose != 0 && this->choose != i - 1 ? --this->choose
													   : this->choose;
			break;
		case arcade::DOWN :
			this->choose != i - 2 && this->choose != i - 2 + j ? ++this->choose
															   : this->choose;
			break;
		default :
			break;
	}
	this->key = arcade::NONE;
}

void u_ncurses::cleanRessources()
{
	this->key = arcade::NONE;
}

arcade::menuLeave u_ncurses::menu(std::map<std::string, void *> &game_lib_name,
								  std::map<std::string, void *> &graphics_lib_name)
{
	if (this->snake.size() == 0) {
		this->loadMap(MAPS_MENU_PATH + std::string("menu") + MAPS_MENU_EXT, 1);
		this->loadMap(MAPS_MENU_PATH + std::string("snake") + MAPS_MENU_EXT,
					  2);
		this->loadMap(MAPS_MENU_PATH + std::string("r_snake") + MAPS_MENU_EXT,
					  3);
		this->loadMap(MAPS_MENU_PATH + std::string("pacman") + MAPS_MENU_EXT,
					  4);
		this->loadMap(MAPS_MENU_PATH + std::string("fantoms") + MAPS_MENU_EXT,
					  5);
		this->loadMap(
				MAPS_MENU_PATH + std::string("centipede") + MAPS_MENU_EXT, 6);
	}
	this->state = arcade::MENU;
	while (this->state == arcade::MENU && this->isAlive()) {
		this->clearWindow();
		this->printMap();
		this->printStatus(game_lib_name, graphics_lib_name);
		this->getKey();
		if (this->key == arcade::RESET) {
			this->key = arcade::NONE;
			auto gameIndex = game_lib_name.begin();
			size_t i = 0;
			for (; i < this->choose &&
				   gameIndex != game_lib_name.end(); ++i, ++gameIndex);
			if (this->choose < game_lib_name.size())
				return {arcade::menuLeave::GAME, gameIndex->first};
			else if (this->choose <
					 game_lib_name.size() + graphics_lib_name.size()) {
				auto libIndex = graphics_lib_name.begin();
				size_t tmp = 0;
				for (; tmp < (this->choose - game_lib_name.size()) &&
					   libIndex != graphics_lib_name.end(); ++tmp, ++libIndex);
				return {arcade::menuLeave::GRAPHIC, libIndex->first};
			}
			this->isExit = true;
			return {arcade::menuLeave::EXIT, std::string()};
		}
		this->actionKey(game_lib_name.size() + 1,
						graphics_lib_name.size() + 1);
		usleep(90000);
	}
	if (!game_lib_name.empty())
		return {arcade::menuLeave::GAME, game_lib_name.begin()->first};
	this->cleanRessources();
	return {arcade::menuLeave::EXIT, std::string()};
}

bool u_ncurses::isAlive()
{
	return this->isOpen;
}

bool u_ncurses::exit()
{
	return isExit;
}

void u_ncurses::openWindow()
{
	if (!this->isOpen) {
		initscr();
		this->isOpen = true;
		nodelay(stdscr, TRUE);
		start_color();
		keypad(stdscr, TRUE);
		init_colors();
		curs_set(0);
		noecho();
		this->clearWindow();
	}
}

void u_ncurses::closeWindow()
{
	if (this->isOpen) {
		this->isOpen = false;
		endwin();
	}
}

void u_ncurses::displayWindow()
{
	if (this->isOpen)
		refresh();
}

void u_ncurses::clearWindow()
{
	if (this->isOpen)
		clear();
}

void u_ncurses::refreshWindow()
{
	if (this->isOpen)
		refresh();
}

void u_ncurses::drawMap(std::vector<std::string> &map)
{
	this->clearWindow();
	size_t j = map.size();
	int y = map[0].size();
	static int color = 1;

	for (size_t i = 0; i < j; ++i) {
		for (size_t c = 0; c < map[i].size(); ++c) {
			if (map[i][c] != ' ') {
				if (map[i][c] == '#')
					color = 7;
				else if (map[i][c] == 'o')
					color = 1;
				else if (map[i][c] >= 'A' && map[i][c] <= 'D')
					color = 4;
				else if (map[i][c] == '0')
					color = 3;
				else if (map[i][c] == '1')
					color = 5;
				else if (map[i][c] == '2')
					color = 6;
				else if (map[i][c] == '3')
					color = 8;
				else if (map[i][c] == '4')
					color = 2;
				else if (map[i][c] == '5')
					color = 3;
				else
					color = 2;
				attron(COLOR_PAIR(color));
				mvprintw(LINES / 2 - (map.size() / 2) + i,
						 COLS / 2 - y + c * 2, "##");
				attroff(COLOR_PAIR(color));
			}
		}
	}
	this->displayWindow();
}

arcade::keys u_ncurses::getKey()
{
	int c = getch();

	switch (c) {
		case KEY_UP:
			this->key = arcade::UP;
			break;
		case KEY_LEFT:
			this->key = arcade::LEFT;
			break;
		case KEY_DOWN:
			this->key = arcade::DOWN;
			break;
		case KEY_RIGHT:
			this->key = arcade::RIGHT;
			break;
		case 27:
			this->key = arcade::NONE;
			this->state = arcade::MENU;
			return arcade::ESC;
		case 10:
			this->key = arcade::RESET;
			break;
		case ' ':
			this->key = arcade::PAUSE;
			break;
		case 't':
			this->key = arcade::SHOOT;
			break;
		case 'n':
			this->key = arcade::NONE;
			return arcade::NEXT_LIB;
		case 'p':
			this->key = arcade::NONE;
			return arcade::PREVIOUS_LIB;
		case 'b':
			this->key = arcade::NONE;
			return arcade::NEXT_GAME;
		case 'o':
			this->key = arcade::NONE;
			return arcade::PREVIOUS_GAME;
		case KEY_BACKSPACE:
			if (this->playerName.size() > 0) {
				this->playerName.erase(this->playerName.size());
				this->playerName.pop_back();
			}
			break;
		default:
			if (this->playerName.size() < 20 &&
				((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
				 (c >= 'a' && c <= 'z')))
				this->playerName += static_cast<char>(c);
			break;
	}
	return this->key;
}

void u_ncurses::createBlocks(const std::string &game_name)
{
	static_cast<void>(game_name);
}

void arcade::Ncurses::playMusic(const std::string &index)
{
	static_cast<void>(index);
};

void arcade::Ncurses::stopMusic(const std::string &index)
{
	static_cast<void>(index);
};

void arcade::Ncurses::playThis(const std::string &music)
{
	static_cast<void>(music);
}

void arcade::Ncurses::createMusic(const std::string &index, const std::string &path)
{
	static_cast<void>(index);
	static_cast<void>(path);
};