//
// EPITECH PROJECT, 2018
// arcade
// File description:
// interface
//

#ifndef IGRAPHICSMODULE_HPP_
#define IGRAPHICSMODULE_HPP_

# include <map>
# include <vector>
# include <iostream>

# define LIB_NAME "lib_arcade_"
# define GRAPHICS_LIB_PATH "./lib/lib_arcade_"
# define GRAPHICS_LIB_EXT ".so"
# define GRAPHICS_PICTURE_PATH "./picture/games/"
# define GAMES_LIB_PATH "./games/lib_arcade_"
# define GAME_DIR "./games/"
# define LIB_DIR "./lib/"
# define GAMES_LIB_EXT ".so"
# define SCOREBOARD "./scoreboard/games/"
# define SCORE_FILE "./score.txt"
# define MAPS_MENU_PATH "./picture/"
# define MAPS_MENU_EXT ".txt"
# define MAPS_PATH "./maps/"
# define MAPS_EXT ".txt"
# define MUSIC_PATH "./audio/music/"
# define SOUND_PATH "./audio/sound/"

namespace arcade {
	typedef struct s_menuLeave {
		enum menuLeaveState {
			GRAPHIC,
			GAME,
			EXIT
		};
		menuLeaveState state;
		std::string path;
	} menuLeave;

	enum keys {
		NONE,
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ESC,
		PAUSE,
		RESET,
		SHOOT,
		NEXT_LIB,
		PREVIOUS_LIB,
		NEXT_GAME,
		PREVIOUS_GAME
	};
	enum state {
		MENU,
		GAME
	};

	enum libType {
		NONE_LIB,
		GRAPHICAL_LIB,
		GAME_LIB
	};

	class IGraphics {
	public:
		virtual  ~IGraphics() = default;
		virtual menuLeave menu(std::map<std::string, void *> &games_lib_name,
					 std::map<std::string, void *> &graphics_lib_name) = 0;
		virtual bool isAlive() = 0;
		virtual bool exit() = 0;
		virtual void openWindow() = 0;
		virtual void closeWindow() = 0;
		virtual void clearWindow() = 0;
		virtual void refreshWindow() = 0;
		virtual void createBlocks(const std::string &game_name) = 0;
		virtual void displayWindow() = 0;
		virtual void drawMap(std::vector<std::string> &map) = 0;
		virtual void createMusic(const std::string &index, const std::string &path) = 0;
		virtual void playMusic(const std::string &index) = 0;
		virtual void stopMusic(const std::string &index) = 0;
		virtual arcade::keys getKey() = 0;
		arcade::libType type;
		arcade::state state;
		std::string playerName;
	};
}

#endif /* !IGRAPHICSMODULE_HPP_ */
