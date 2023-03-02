/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** load_systems
*/

#include "../Include/registry.hpp"
#include "../Include/systems.hpp"

/**
 * @file load_systems.cpp
 */

/**
 * @brief Load all the systems in the registry.
 *
 * @param reg Container of all the systems.
 */

void load_system(registry &reg)
{
    reg.add_system<component::interaction>(interaction_system);
    reg.add_system<component::image, component::rect, component::animation>(animation_system);
    reg.add_system<component::collusion, component::image>(collusion_system);
    // reg.add_system<component::position, component::network>(network_position_system);
}