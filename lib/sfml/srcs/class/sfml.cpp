//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml class
//

#include "sfml.hpp"

u_sfml::Sfml()
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

u_sfml::~Sfml()
{
}

bool u_sfml::isAlive()
{
	return this->window.isOpen();
}

bool u_sfml::exit()
{
	return this->isExit;
}

void u_sfml::closeWindow()
{
	if (this->window.isOpen())
		this->window.close();
}

void u_sfml::displayWindow()
{
	this->window.display();
}

void u_sfml::clearWindow()
{
	this->window.clear(sf::Color::Black);
}

void u_sfml::refreshWindow()
{
}

std::unique_ptr<sf::Sprite> &u_sfml::getSpriteByCharacter(std::string character, const size_t &loop)
{
	if (character >= "A" && character <= "D") {
		std::unique_ptr<sf::Sprite> &sprite = this->gifs["D"];
		sprite->setTextureRect(sf::IntRect(loop * 32, ((character[0] -
								'A') * 32), 32, 32));
		return sprite;
	}
	else if (character >= "E" && character <= "P") {
		std::unique_ptr<sf::Sprite> &sprite = this->gifs["P"];

		int x = 0;
		char tmp = 'E';

		for (; tmp <= 'P' ; tmp += 4, x+= 2)
			if (character[0] >= tmp && character[0] <= (tmp + 3))
				break;
		sprite->setTextureRect(sf::IntRect((loop + x) * 32,
						   (character[0] - tmp) * 32, 32, 32));
		return sprite;
	}
	else if (character >= "0" && character <= "9") {
		std::unique_ptr<sf::Sprite> &sprite = this->gifs["0"];
		int x = 0;
		char tmp = '0';

		for (; tmp <= '9' ; tmp += 1)
			if (character[0] >= tmp && character[0] <= (tmp + 3))
				break;
		sprite->setTextureRect(sf::IntRect((x) * 32,
										   (character[0] - tmp) * 32, 32, 32));
		return sprite;
	}
	std::unique_ptr<sf::Sprite> &sprite = this->blocks[character];
	return sprite;

}

void u_sfml::drawMap(std::vector<std::string> &map)
{
	static size_t loop = 0;
	size_t margin_x, margin_y, margin;

	margin = 32;
	margin_y = 0;
	static sf::Clock clock;
	static float last =  0.0;
	sf::Time elapsed1 = clock.getElapsedTime();
	for (auto line = map.begin() ; line < map.end() ; ++line) {
		margin_x = 0;
		for (size_t x = 0 ; x < line->size() ; ++x) {
			std::unique_ptr<sf::Sprite> &sprite =
				this->getSpriteByCharacter(line->substr(x, 1), loop);
			if (sprite) {
				if (line->substr(x ,1) != " ") {
					std::unique_ptr<sf::Sprite> &under = this->blocks[" "];
					under->setPosition(sf::Vector2f(margin_x, margin_y));
					this->window.draw(*under);
				}
				sprite->setPosition(sf::Vector2f(margin_x, margin_y));
				this->window.draw(*sprite);
			}
			margin_x += margin;
		}
		margin_y += margin;
	}
	if (last + 0.26 <= elapsed1.asSeconds()) {
		last +=  0.26;
		loop = loop == 0 ? 1 : 0;
	}
	this->displayWindow();
}

arcade::keys u_sfml::getKey()
{
	sf::Event event{};

	this->eventKey = sf::Keyboard::Unknown;
	while (this->window.pollEvent(event))
		this->sfml_event(event);
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

void u_sfml::openWindow()
{
	if (!this->window.isOpen()) {
		this->window.create(sf::VideoMode(this->width, this->height),
				    "Sfml", sf::Style::Close);
		this->window.setFramerateLimit(60);
	}
}

//RESSOURCES FUNCTION
std::string u_sfml::my_substr(const std::string &str, const std::string &after,
				    const std::string &extension)
{
	std::string result = str;

	result = result.substr(result.find(after) + after.size());
	result = result.substr(0, result.size() - extension.size());
	return result;
}

void u_sfml::cleanRessources()
{
	this->key = arcade::NONE;
	this->eventKey = sf::Keyboard::Key();
}
