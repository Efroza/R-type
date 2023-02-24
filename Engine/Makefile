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
	BaseComponent/interaction.cpp	\
	BaseComponent/rect.cpp	\
	BaseSystems/animation_system.cpp	\
	BaseSystems/interaction_system.cpp	\
	BaseSystems/collusion_system.cpp	\
	ParseComponent/AParseComponent.cpp	\
	ParseComponent/AParseInteraction.cpp	\
	ParseComponent/parse_position.cpp	\
	ParseComponent/parse_image.cpp	\
	ParseComponent/parse_rect.cpp	\
	ParseComponent/parse_animation.cpp	\
	ParseComponent/parse_interaction.cpp	\
	Parsing/parsing.cpp	\
	Parsing/handling_interaction.cpp	\
	Parsing/Yaml.cpp	\
	Parsing/handling_component_system.cpp	\


CC	= 	g++ -o

OBJS	= 	$(SRCS:.cpp=.o)

NAME	= 	rtype

CXXFLAGS	=	-I ./Include -I ./BaseComponent -I ./ParseComponent -I ./Parsing -std=c++20 \
-I ./Interaction -I ./Interaction/Include -I ./Graphic -I ./ComponentSystem #  -Wall -Wextra -Werror -ljsoncp

RM	= 	rm -f

all: 		$(NAME)

$(NAME): 	$(OBJS)
	 	$(CC) $(NAME) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system -ljsoncpp -ldl -lyaml-cpp

debug:	$(OBJS)
		$(CC) $(NAME) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system -ljsoncpp -lyaml-cpp -ldl -g3

clean:
		$(RM) $(OBJS)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all

.PHONY: 	all clean fclean re
