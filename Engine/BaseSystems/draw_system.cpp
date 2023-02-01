/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** draw_system
*/

#include "registry.hpp"
#include "draw.hpp"
#include "image.hpp"

void draw_system(registry &reg, sparse_array<component::draw> &draw, sparse_array<component::image> &image)
{
    sf::RenderWindow &window = reg.get_window();

    for (size_t i = 0; i < draw.size() && i < image.size(); ++i) {
        if (draw[i] && image[i])
            window.draw(image[i].value().get_sprite());
    }
}