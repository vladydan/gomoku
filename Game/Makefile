CC	= g++

RM	= rm -f

NAME	= gomoku

SRCS	= main.cpp \
	  Game.cpp \
	  Player.cpp

OBJS	= $(SRCS:.cpp=.o)

CFLAGS	+= -I. -Wall -Werror -Wextra -W

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all
