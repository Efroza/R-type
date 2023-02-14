/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** gravity_system
*/

#include "registry.hpp"
#include "position.hpp"
#include "image.hpp"

void gravity_system(registry &reg, sparse_array<component::image> &images, sparse_array<component::position> & positions)
{
    sf::RenderWindow &window = reg.get_window();

    for (size_t i = 0; i < positions.size() && i < images.size(); ++i) {
        if (positions[i] && images[i]) {
            images[i].value().get_sprite().move(0, 20);
        }
    }
}