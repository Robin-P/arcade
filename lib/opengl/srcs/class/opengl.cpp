//
// EPITECH PROJECT, 2018
// arcade
// File description:
// opengl class
//

#include "opengl.hpp"

u_opengl::Opengl()
{
	this->type = arcade::libType::GRAPHICAL_LIB;
	this->eventKey = sf::Keyboard::Key::Unknown;
	this->GamePathName = "";
	this->GraphicsPathName = "";
	this->indexBackgrounds = DEFAULT;
	this->key = arcade::NONE;
	this->isExit = false;
	this->width = 1280;
	this->height = 864;
	this->addFont("ARIAL", ARIAL);
}

u_opengl::~Opengl()
{
}

bool u_opengl::isAlive()
{
	return this->window.isOpen();
}

bool u_opengl::exit()
{
	return this->isExit;
}

void u_opengl::closeWindow()
{
	if (this->window.isOpen())
		this->window.close();
}

void u_opengl::displayWindow()
{
	this->window.display();
}

void u_opengl::clearWindow()
{
	this->window.clear(sf::Color::Black);
}

void u_opengl::refreshWindow()
{
}

void u_opengl::drawMap(std::vector<std::string> &map)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, static_cast<double>(this->width / this->height), 1,
				   1000);
	glEnable(GL_DEPTH_TEST);
	gluLookAt(0, map.size() / 3, map.size() * 2, 0, 0, 0, 0, 0, 1);
	glRotatef(90, 0, 0, 1);
	glRotatef(-10, 0, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	clearOpengl();
	draw3dMap(map);
	refreshOpengl();
	this->displayWindow();;
	this->window.resetGLStates();
}

arcade::keys u_opengl::getKey()
{
	sf::Event event{};

	this->eventKey = sf::Keyboard::Unknown;
	while (this->window.pollEvent(event))
		this->opengl_event(event);
	switch (this->eventKey) {
		case (sf::Keyboard::Escape) : this->state = arcade::MENU ; this->key = arcade::ESC; break;
		case (sf::Keyboard::Right) : this->key = arcade::RIGHT; break;
		case (sf::Keyboard::Left) : this->key = arcade::LEFT; break;
		case (sf::Keyboard::Up) : this->key = arcade::UP; break;
		case (sf::Keyboard::Down) : this->key = arcade::DOWN; break;
		case (sf::Keyboard::Return) : this->key = arcade::NONE; return arcade::RESET;
		case (sf::Keyboard::Space) : this->key = arcade::PAUSE; break;
		case (sf::Keyboard::T) : this->key = arcade::NONE; return arcade::SHOOT;
		case (sf::Keyboard::N) : this->key = arcade::NONE; return arcade::NEXT_LIB;
		case (sf::Keyboard::P) : this->key = arcade::NONE; return arcade::PREVIOUS_LIB;
		case (sf::Keyboard::B) : this->key = arcade::NONE; return arcade::NEXT_GAME;
		case (sf::Keyboard::O) : this->key = arcade::NONE; return arcade::PREVIOUS_GAME;
		default: break;
	}
	return this->key;
}

void u_opengl::openWindow()
{
	if (!this->window.isOpen()) {
		this->window.create(sf::VideoMode(this->width, this->height), "OpenGl",
							sf::Style::Close, sf::ContextSettings(24));

		this->window.setFramerateLimit(60);
	}
}

//RESSOURCES FUNCTION
std::string u_opengl::my_substr(const std::string &str, const std::string &after,
								const std::string &extension)
{
	std::string result = str;

	result = result.substr(result.find(after) + after.size());
	result = result.substr(0, result.size() - extension.size());
	return result;
}

void u_opengl::cleanRessources()
{
	this->key = arcade::NONE;
	this->eventKey = sf::Keyboard::Key();
}
