/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** collusion_system
*/

#include "../Include/systems.hpp"

/**
 * @file collusion_system.cpp
 */

/**
 * @brief Check if two entities are colliding.
 *
 * @param reg Registry of the engine, used to contain all the component system.
 * @param collusion Component system of the collision.
 * @param image To get the sprite of the entity which is colliding.
 */

void collusion_system(registry &reg, sparse_array<component::collusion> &collusion, sparse_array<component::image> &image)
{
    if (image.size() == 0)
        return;
    for (int i = 0; i < image.size(); i++) {
        for (int j = 0; j < image.size(); j++) {
            if (image[i] && image[j]) {
                // if (i != j && image[i].value().get_sprite().getGlobalBounds().intersects(image[j].value().get_sprite().getGlobalBounds())) {
                //     // image[j].value().get_sprite().setColor(sf::Color::Red);
                //     reg.kill_entity(j);
                //     return;
                // }
            }
        }
    }
}