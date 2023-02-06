/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** position_system
*/

#include "registry.hpp"
#include "position.hpp"
#include "image.hpp"

void position_system(registry &reg, sparse_array<component::position> &position, sparse_array<component::image> &image)
{
    sf::RenderWindow &window = reg.get_window();

    for (size_t i = 0; i < position.size() && i < image.size(); ++i)
        if (position[i] && image[i])
            image[i].value().get_sprite().setPosition(position[i].value().pos);
}