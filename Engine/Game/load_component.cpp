/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** load_component
*/

#include "../Include/registry.hpp"
#include "../Include/systems.hpp"

/**
 * @file load_component.cpp
 */

/**
 * @brief Load all the components in the registry.
 *
 * @param reg Container of all the components.
 */

void load_component(registry &reg)
{
    reg.register_component<component::image>();
    reg.register_component<component::position>();
    reg.register_component<component::draw>();
    reg.register_component<component::rect>();
    reg.register_component<component::interaction>();
    reg.register_component<component::animation>();
    reg.register_component<component::collusion>();
    reg.register_component<component::network>();
    reg.register_component<component::network_player>();
}