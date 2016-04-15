##
## Makefile for snake in /home/simomb_s/MyGithub/cpp_arcade/snake
##
## Made by stephanedarcy simomba
## Login   <simomb_s@epitech.net>
##
## Started on  Fri Apr 15 08:12:18 2016 stephanedarcy simomba
## Last update Fri Apr 15 08:12:58 2016 stephanedarcy simomba
##

CC	= g++

NAME	= snake

CPPFLAGS	+= -W -Wall -Werror -Wextra
CPPFLAGS	+= -Iinclude

SRCS	= main.cpp \
	snake.cpp

OBJS	= $(SRCS:.cpp=.o)

RM	= rm -f
PRINTF	= @printf

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lncurses
	$(PRINTF) '\033[1;32m> Compiled\033[0m\n'

clean:
	$(RM) $(OBJS)
	$(PRINTF) '\033[1;35m> Directory cleaned\033[0m\n'

fclean: clean
	$(RM) $(NAME)
	$(PRINTF) '\033[1;35m> Remove executable\033[0m\n'

re: fclean all

.PHONY: all clean fclean re
