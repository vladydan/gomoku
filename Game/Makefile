CC	= g++

RM	= rm -f

NAME	= gomoku

SRCS	= main.cpp \
	  Game.cpp \
	  Player.cpp

OBJS	= $(SRCS:.cpp=.o)

CFLAGS	+= -I. -Wall -Werror -Wextra -W -std=c++11

all: $(NAME)

%.o:	%.cpp
	g++ $(CFLAGS) -c -o $@ $<

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
