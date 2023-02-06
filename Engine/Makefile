##
## EPITECH PROJECT, 2023
## makefile
## File description:
## Makefile
##

SRCS	=	Game/main.cpp	\
	Game/load_component.cpp	\
	Game/load_systems.cpp	\
	BaseComponent/image.cpp	\
	BaseSystems/draw_system.cpp	\
	BaseSystems/position_system.cpp	\


CC	= 	g++ -o

OBJS	= 	$(SRCS:.cpp=.o)

NAME	= 	rtype

CXXFLAGS	=	-I ./Include -I ./BaseComponent -std=c++20 #  -Wall -Wextra -Werror -ljsoncp

RM	= 	rm -f

all: 		$(NAME)

$(NAME): 	$(OBJS)
	 	$(CC) $(NAME) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system

debug:	$(OBJS)
		$(CC) $(NAME) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system -g3

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
