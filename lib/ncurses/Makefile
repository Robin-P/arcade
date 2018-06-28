NAME		=	lib_arcade_ncurses.so

CC		=	g++ -lpthread -pthread

RM		=	rm -f

SRCS		=	./srcs/ncurses_launch.cpp		\
			./srcs/class/ncurses.cpp			\
			./../../srcs/class/exception/exception.cpp

OBJS		=	$(SRCS:.cpp=.o)

CPPFLAGS	=	-I./header/class			\
			-I../../header/interface/			\
			-I../../header/class/exception/

CPPFLAGS	+=	-W -Wall -Wextra -fPIC

LDFLAGS		=	-shared -lncurses

.cpp.o:
			@$(CC) $(CPPFLAGS) -c $< -o $@ && \
			printf "[\033[1;32mcompiled\033[0m] % 39s\n" $< | tr ' ' '.' || \
			printf "[\033[1;31mfailed\033[0m] % 41s\n" $< | tr ' ' '.'

all: 			$(NAME)

$(NAME):		$(OBJS)
			@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME) && \
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
