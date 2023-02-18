##
## EPITECH PROJECT, 2023
## makefile
## File description:
## Makefile
##

SRCS	=	Game/main.cpp	\
	Game/load_component.cpp	\
	Game/load_systems.cpp	\
	Game/handle_entity.cpp	\
	BaseComponent/image.cpp	\
	BaseComponent/interaction.cpp	\
	BaseComponent/rect.cpp	\
	BaseSystems/draw_system.cpp	\
	BaseSystems/position_system.cpp	\
	BaseSystems/animation_system.cpp	\
	BaseSystems/rect_system.cpp	\
	BaseSystems/interaction_system.cpp	\
	Interaction/up_deplacement.cpp	\
	Interaction/left_deplacement.cpp	\
	Interaction/right_deplacement.cpp	\
	Interaction/down_deplacement.cpp	\
	ParseComponent/AParseComponent.cpp	\
	ParseComponent/parse_draw.cpp	\
	ParseComponent/parse_position.cpp	\
	ParseComponent/parse_image.cpp	\
	ParseComponent/parse_rect.cpp	\
	ParseComponent/parse_animation.cpp	\
	Parsing/parsing.cpp	\


CC	= 	g++ -o

OBJS	= 	$(SRCS:.cpp=.o)

NAME	= 	rtype

CXXFLAGS	=	-I ./Include -I ./BaseComponent -I ./ParseComponent -I ./Parsing -std=c++20 #  -Wall -Wextra -Werror -ljsoncp

RM	= 	rm -f

all: 		$(NAME)

$(NAME): 	$(OBJS)
	 	$(CC) $(NAME) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system -ljsoncpp

debug:	$(OBJS)
		$(CC) $(NAME) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system -ljsoncpp -g3

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
