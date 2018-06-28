//
// EPITECH PROJECT, 2018
// ghost
// File description:
// ghost
//

#include "astar.hpp"
#include "ghost.hpp"

using u_ghost = arcade::Ghost;

u_ghost::Ghost(int x, int y, char _id) : id(_id)
{
	this->last = ' ';
	this->order = {-1, -1};
	this->pos = {x, y};
	this->mod = arcade::Ghost::INVINSIBLE;
	this->prevLoop = std::chrono::system_clock::now();
	srand(time(nullptr));
}

u_ghost::~Ghost()
{
}


void u_ghost::setOrder(position order)
{
	this->order = order;
}

void u_ghost::addGhost(std::vector<std::unique_ptr<arcade::Ghost>> &array,
		       std::vector<std::string> &map)
{
	for (auto &ghost : array) {
		map[ghost->pos.x][ghost->pos.y] = ghost->id;
	}
}

void u_ghost::createGhost(std::vector<std::unique_ptr<arcade::Ghost>> &array, int nb, const char &firstId)
{
	int x = 12;
	int y = 17;
	char tmpId = firstId;
	position order = {12, 17};

	for (int a = 0 ; a < nb ; ++a, ++y) {
		std::unique_ptr<arcade::Ghost> ghost = std::make_unique<arcade::Ghost>(x, y, tmpId);
		array.push_back(std::move(ghost));
		array[a]->setOrder(order);
		tmpId += 4;
	}
}

bool u_ghost::validMove(const char &aCase)
{
	return (aCase == 'o' || aCase == 'b' || aCase == ' ' || (aCase >= 'A' && aCase <= 'D'));
}

int u_ghost::moveHome(std::vector<std::string> &map)
{

	std::vector<Pos> nextPos;
	Astar path(map);

	this->pacman = {12, 16};
	this->order = {12, 16};
	while (!this->validMove(map[this->order.x][this->order.y])) {
		this->order.y += 1;
		this->pacman.y += 1;
	}
	nextPos = path.findPath({this->pos.y, this->pos.x}, {this->order.y, this->order.x});
	if (!nextPos.empty() && nextPos.size() > 1) {
		std::reverse(nextPos.begin(), nextPos.end());
		if (this->validMove(map[nextPos[1].y][nextPos[1].x])) {
			map[this->pos.x][this->pos.y] = this->last;
			char tmpId = this->id;
			if (nextPos[1].y > this->pos.x)
				tmpId += 2; /* DOWN */
			else if (nextPos[1].y < this->pos.x)
				tmpId += 0; /* UP */
			else if (nextPos[1].x > this->pos.y)
				tmpId += 1; /* RIGHT */
			else if (nextPos[1].x < this->pos.y)
				tmpId += 3; /* LEFT */
			this->pos.x = nextPos[1].y;
			this->pos.y = nextPos[1].x;
			last = (this->pos.x == this->pacman.x && this->pos.y == this->pacman.y ? ' ' : map[this->pos.x][this->pos.y]);
			map[this->pos.x][this->pos.y] = tmpId;
		}
	}
        return 0;
}

int u_ghost::move(std::vector<std::string> &map)
{
	if (this->pos.x == this->pacman.x && this->pos.y == this->pacman.y) {
		map[this->pos.x][this->pos.y] = ' ';
		return 1;
	}
	this->order = this->pacman;
	std::vector<Pos> nextPos;
	Astar path(map);

	nextPos = path.findPath({this->pos.y, this->pos.x}, {this->order.y, this->order.x});
	if (!nextPos.empty() && nextPos.size() > 1) {
		std::reverse(nextPos.begin(), nextPos.end());
		if (this->validMove(map[nextPos[1].y][nextPos[1].x])) {
			map[this->pos.x][this->pos.y] = this->last;
			char tmpId = this->id;
			if (nextPos[1].y > this->pos.x)
				tmpId += 2; /* DOWN */
			else if (nextPos[1].y < this->pos.x)
				tmpId += 0; /* UP */
			else if (nextPos[1].x > this->pos.y)
				tmpId += 1; /* RIGHT */
			else if (nextPos[1].x < this->pos.y)
				tmpId += 3; /* LEFT */
			this->pos.x = nextPos[1].y;
			this->pos.y = nextPos[1].x;
			last = (this->pos.x == this->pacman.x && this->pos.y == this->pacman.y ? ' ' : map[this->pos.x][this->pos.y]);
			map[this->pos.x][this->pos.y] = tmpId;
		}
	}
	return 0;
}
