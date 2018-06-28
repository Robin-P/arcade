//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml class
//

#ifndef LIB_SFML_CLASS_HPP_
#define LIB_SFML_CLASS_HPP_

# include <memory>
# include <map>
# include <SFML/Audio.hpp>
# include <SFML/Window.hpp>
# include <SFML/Window/Mouse.hpp>
# include <SFML/System.hpp>
# include <SFML/Graphics.hpp>
# include <iostream>
# include "IGraphics.hpp"
# include "exception.hpp"
# define ARIAL "font/arial.ttf"
# define DEFAULT "menu"

namespace arcade {
	class Sfml : public IGraphics {
	public:
		Sfml();
		~Sfml() override;
		/* GAME FUNCTION */
		arcade::menuLeave menu(std::map<std::string, void *> &games_lib_name,
				 std::map<std::string, void *> &graphics_lib_name) override;
		bool exit() override;
		void closeWindow() override;
		void sfml_event(sf::Event &event);
		void displayWindow() override;
		void drawMenuText();
		void drawMap(std::vector<std::string> &map) override;
		void openWindow() override;
		void clearWindow() override;
		void refreshWindow() override;
		bool isAlive() override;
		arcade::keys getKey() override;
		/*  RESSOURCE FUNCTION*/
		//MENU
		void initMenu(std::map<std::string, void *> &game_lib_name,
			      std::map<std::string, void *> &graphics_lib_name);
		arcade::menuLeave leaveMenu();
		//SOUND
		void playSound(const std::string &index);
		void createSound(const std::string &index, const std::string &path);
		void addSoundBuffer(const std::string &index, const std::string &path);
		void addSound(const std::string &index);
		void destroyMusic();
		void playMusic(const std::string &index) override;
		void createMusic(const std::string &index, const std::string &path) override;
		void stopMusic(const std::string &index);
		//FONTS
		void addFont(const std::string &key, std::unique_ptr<sf::Font> &font);
		void addFont(const std::string &key, const std::string &maccro);
		std::unique_ptr<sf::Font> &getFont(const std::string &name);
		//SCOREBOARDS
		void displayScoreboard(const std::string &font_name, const std::string &game_name,
				       const size_t &size, const sf::Color &outlineColor,
				       const sf::Color &textColor, sf::Vector2f position);
		void createScoreboard(std::map<std::string, void *> &game_lib_name);
		std::string getScore(std::string &game_name);
		//TEXTS
		void drawText(const std::string &font_name, const std::string &line,
			      const size_t &size, const sf::Color &outlineColor,
			      const sf::Color &textColor, const sf::Vector2f &position);
		//BUTTONS
		void createButtons(std::map<std::string, void *> &game_lib_name,
				   std::map<const std::string, sf::RectangleShape> &container,
				   const std::string &after, const std::string &before,
				   sf::Vector2f position);
		void buttonClick();
		void mouseAction();
		//SPRITES & TEXTURES
		std::unique_ptr<sf::Sprite> &getSpriteByCharacter(std::string character,
								  const size_t &loop);
		void createBlocks(const std::string &game_name);
		bool createTexture(const std::string &index, const std::string &path,
				  std::map<const std::string, std::unique_ptr<sf::Texture>> &textures);
		bool createSprite(const std::string &index, const std::string &path,
				  std::map<const std::string, std::unique_ptr<sf::Sprite>> &sprites,
				  std::map<const std::string, std::unique_ptr<sf::Texture>> &textures);
		void createBackgrounds(std::map<std::string, void *> &game_lib_name);

		void cleanRessources();
		std::string my_substr(const std::string &str, const std::string &after,
				      const std::string &extension);
		//EVENTS
		void keyManager(sf::Keyboard::Key &code);
		void addCharacterToPrompt(char character);
		void displayPrompt();
	public:
		sf::RenderWindow window;
		size_t height;
		size_t width;
		bool isExit;
		sf::Keyboard::Key eventKey;
		arcade::keys key;
		std::string GamePathName;
		std::string GraphicsPathName;

		//RESSOURCES VARS
		std::string indexBackgrounds;
		std::map<const std::string, std::unique_ptr<sf::SoundBuffer>> buffers;
		std::map<const std::string, std::unique_ptr<sf::Sound>> sounds;
		std::map<const std::string, std::string> scoreboards;
		std::map<const std::string, sf::RectangleShape> buttons_games;
		std::map<const std::string, sf::RectangleShape> buttons_graphics;
		std::map<const std::string, std::unique_ptr<sf::Music>> musics;
		std::map<const std::string, std::unique_ptr<sf::Sprite>> backgrounds;
		std::map<const std::string, std::unique_ptr<sf::Sprite>> blocks;
		std::map<const std::string, std::unique_ptr<sf::Texture>> textures;
		std::map<const std::string, std::unique_ptr<sf::Sprite>> gifs;
		std::map<const std::string, std::unique_ptr<sf::Font>> fonts;
	};
}

using u_sfml = arcade::Sfml;
#endif /* !LIB_SFML_CLASS_HPP_ */
