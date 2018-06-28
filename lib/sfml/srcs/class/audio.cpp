//
// EPITECH PROJECT, 2018
// arcade
// File description:
// LIB SFML AUDIO
//

#include "sfml.hpp"

void u_sfml::addSoundBuffer(const std::string &index, const std::string &path)
{
	std::unique_ptr<sf::SoundBuffer> buffer = std::make_unique<sf::SoundBuffer>();

	if (!buffer->loadFromFile(path))
		throw arcade::Exception("SFML LIB", "Audio file: \'" + path + "\' not found");
	this->buffers[index] = std::move(buffer);
}

void u_sfml::addSound(const std::string &index)
{
	std::unique_ptr<sf::Sound> sound = std::make_unique<sf::Sound>();

	if (!this->buffers[index])
		throw arcade::Exception("SFML LIB", "Sound: \'" + index + "\' not found");
	sound->setBuffer(*this->buffers[index]);
	this->sounds[index] = std::move(sound);
}

void u_sfml::createSound(const std::string &index, const std::string &path)
{
	this->addSoundBuffer(index, path);
	this->addSound(index);
}

void u_sfml::playSound(const std::string &index)
{
	if (!this->sounds[index])
		throw arcade::Exception("SFML LIB", "Play sound: \'" + index + "\' not found");
	this->sounds[index]->play();
}

void u_sfml::createMusic(const std::string &index, const std::string &path)
{
	std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

	if (!music->openFromFile(path))
		throw arcade::Exception("SFML LIB", "Add music: \'" + path + "\' not found");
	if (!this->musics[index])
		this->musics[index] = std::move(music);
}

void u_sfml::playMusic(const std::string &index)
{
	if (!this->musics[index])
		throw arcade::Exception("SFML LIB", "Play music: \'" + index + "\' not found");
	this->musics[index]->play();
}

void u_sfml::destroyMusic()
{
	for (auto &music : this->musics) {
		if (music.second->getStatus() == sf::Music::Status::Playing)
			music.second->stop();
	}
}

void u_sfml::stopMusic(const std::string &index)
{
	if (!this->musics[index])
		throw arcade::Exception("SFML LIB", "Play music: \'" + index + "\' not found");
	this->musics[index]->stop();
}