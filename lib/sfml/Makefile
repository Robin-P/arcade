NAME		=	lib_arcade_sfml.so

CC		=	g++

RM		=	rm -f

SRCS		=	./srcs/sfml_launch.cpp				\
			./srcs/class/sfml.cpp				\
			./srcs/class/audio.cpp				\
			./srcs/class/button.cpp				\
			./srcs/class/event.cpp				\
			./srcs/class/font.cpp				\
			./srcs/class/menu.cpp				\
			./srcs/class/prompt.cpp				\
			./srcs/class/text.cpp				\
			./srcs/class/scoreboard.cpp			\
			./srcs/class/textureAndSprite.cpp		\
			./../../srcs/class/exception/exception.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-I./header/class/				\
			-I../../header/interface/			\
			-I../../header/class/exception/

CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		=	-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -shared

.cpp.o:
			@$(CC) $(CPPFLAGS) -c $< -o $@ && \
			printf "[\033[1;32mcompiled\033[0m] % 39s\n" $< | tr ' ' '.' || \
			printf "[\033[1;31mfailed\033[0m] % 41s\n" $< | tr ' ' '.'

all: 			$(NAME)

$(NAME):		$(OBJS)
			@$(CC) $(OBJS) $(CPPFLAGS) $(LDFLAGS) -o $(NAME) && \
			(printf "[\033[1;36mbuilt\033[0m] % 42s\n" $(NAME) | tr ' ' '.' || \
			printf "[\033[1;31mfailed\033[0m] % 41s\n" $(NAME) | tr ' ' '.') && \
			mv $(NAME) ../.

clean:
			@$(RM) $(OBJS) && \
			printf "[\033[1;31mdeleted\033[0m] % 40s\n" $(OBJS) | tr ' ' '.' || \
			printf "[\033[1;31mdeleted\033[0m] % 40s\n" $(OBJS) | tr ' ' '.'

fclean: 		clean
			@cd ../ && \
			$(RM) $(NAME) && \
			printf "[\033[1;31mdeleted\033[0m] % 40s\n" $(NAME) | tr ' ' '.' || \
			printf "[\033[1;31mdeleted\033[0m] % 40s\n" $(NAME) | tr ' ' '.'

re:			fclean all

.PHONY: 		all clean fclean re
