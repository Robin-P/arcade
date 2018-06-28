//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml lib texture and sprite
//

#include "sfml.hpp"

bool u_sfml::createTexture(const std::string &index, const std::string &path,
						   std::map<const std::string, std::unique_ptr<sf::Texture>> &map)
{
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

	if (!texture->loadFromFile(path))
		return false;
	map[index] = std::move(texture);
	return true;
}

bool u_sfml::createSprite(const std::string &index, const std::string &path,
						  std::map<const std::string, std::unique_ptr<sf::Sprite>> &spritesMap,
						  std::map<const std::string, std::unique_ptr<sf::Texture>> &texturesMap)
{
	if (!this->createTexture(index, path, textures))
		return false;
	spritesMap[index] = std::make_unique<sf::Sprite>(*texturesMap[index]);
	return true;
}

void u_sfml::createBackgrounds(std::map<std::string, void *> &lib_name)
{
	std::string str;

	if (!this->createSprite(DEFAULT, "./picture/background.png",
							this->backgrounds, this->textures))
		throw arcade::Exception("SFML LIB",
								"Menu picture/background.png was missing");
	for (auto game_name = lib_name.begin();
		 game_name != lib_name.end(); ++game_name) {
		str = this->my_substr(game_name->first, GAMES_LIB_PATH, GAMES_LIB_EXT);
		this->createSprite(str,
						   GRAPHICS_PICTURE_PATH + str + "/" + str + ".png",
						   this->backgrounds, this->textures);
	}
}

void u_sfml::createBlocks(const std::string &game)
{
	this->createSprite("#", GRAPHICS_PICTURE_PATH + game + "/wall.png",
					   this->blocks, this->textures);
	this->createSprite(" ", GRAPHICS_PICTURE_PATH + game + "/ground.png",
					   this->blocks, this->textures);
	this->createSprite("D", GRAPHICS_PICTURE_PATH + game + "/player.png",
					   this->gifs, this->textures);
	this->createSprite("P", GRAPHICS_PICTURE_PATH + game + "/pokemon.png",
					   this->gifs, this->textures);
	this->createSprite("0", GRAPHICS_PICTURE_PATH + game + "/decor.png",
					   this->gifs, this->textures);
	this->createSprite("o", GRAPHICS_PICTURE_PATH + game + "/food.png",
					   this->blocks, this->textures);
	this->createSprite("b", GRAPHICS_PICTURE_PATH + game + "/bonus.png",
					   this->blocks, this->textures);
}
