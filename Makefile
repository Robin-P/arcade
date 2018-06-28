NAME		=	arcade

CC		=	g++

RM		=	rm -f

SRCS		=	./srcs/main.cpp				\
			./srcs/class/console.cpp		\
			./srcs/class/scoreboard.cpp		\
			./srcs/class/switch_lib.cpp		\
			./srcs/class/switch_game.cpp		\
			./srcs/class/tools.cpp			\
			./srcs/class/exception/exception.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-I./include/				\
			-I./header/class/ 			\
			-I./header/class/exception/		\
			-I./header/interface/

CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		=	-ldl -fPIC

.cpp.o:
			@$(CC) $(CPPFLAGS) -c $< -o $@ && \
			printf "[\033[1;32mcompiled\033[0m] % 39s\n" $< | tr ' ' '.' || \
			printf "[\033[1;31mfailed\033[0m] % 41s\n" $< | tr ' ' '.'

all: 			$(NAME)


$(NAME):		$(OBJS)
			@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME) && \
			printf "[\033[1;36mbuilt\033[0m] % 42s\n" $(NAME) | tr ' ' '.' || \
			printf "[\033[1;31mfailed\033[0m] % 41s\n" $(NAME) | tr ' ' '.' && \
			cd lib/sfml/ && make && \
			cd - && \
			cd lib/ncurses/ && make && \
			cd - && \
			cd lib/opengl/ && make && \
			cd - && \
                        cd games/centipede/ && make && \
			cd - && \
			cd games/nibbler/ && make && \
			cd - && \
			cd games/pacman/ && make && \
			cd -

clean:
			@cd lib/sfml/ && make clean && \
			cd - && \
			cd lib/ncurses/ && make clean && \
			cd - && \
			cd lib/opengl/ && make clean && \
			cd - && \
                        cd games/centipede/ && make clean && \
			cd - && \
			cd games/nibbler/ && make clean && \
			cd - && \
			cd games/pacman/ && make clean && \
			cd - && \
			$(RM) $(OBJS) && \
			printf "[\033[1;31mdeleted\033[0m] % 40s\n" $(OBJS) | tr ' ' '.' || \
			printf "[\033[1;31mdeleted\033[0m] % 40s\n" $(OBJS) | tr ' ' '.'

fclean: 		clean
			@cd lib/sfml/ && make fclean && \
			cd - && \
			cd lib/ncurses/ && make fclean && \
			cd - && \
			cd lib/opengl/ && make fclean && \
			cd - && \
                        cd games/centipede/ && make fclean && \
			cd - && \
			cd games/nibbler/ && make fclean && \
			cd - && \
			cd games/pacman/ && make fclean && \
			cd - && \
			$(RM) $(NAME) && \
			printf "[\033[1;31mdeleted\033[0m] % 40s\n" $(NAME) | tr ' ' '.' || \
			printf "[\033[1;31mdeleted\033[0m] % 40s\n" $(NAME) | tr ' ' '.'

re:			fclean core
			@cd lib/sfml/ && make re && \
			cd - && \
			cd lib/ncurses/ && make re && \
			cd - && \
			cd lib/opengl/ && make re && \
			cd - && \
                        cd games/centipede/ && make re && \
			cd - && \
			cd games/pacman/ && make re && \
			cd - && \
			cd games/nibbler/ && make re && \
			cd -

core:			$(OBJS)
			@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME) && \
			printf "[\033[1;36mbuilt\033[0m] % 42s\n" $(NAME) | tr ' ' '.' || \
			printf "[\033[1;31mfailed\033[0m] % 41s\n" $(NAME) | tr ' ' '.'
games:
			@cd games/nibbler/ && make && \
			cd - && \
                        cd games/centipede/ && make && \
			cd - && \
			cd games/pacman/ && make && \
			cd -

graphicals:
			@cd lib/sfml/ && make && \
			cd - && \
			cd lib/opengl/ && make && \
			cd - && \
			cd lib/ncurses/ && make && \
			cd -

.PHONY: 		all clean fclean re core games graphicals
