/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** load_component
*/

#include "registry.hpp"
#include "systems.hpp"

void load_component(registry &reg)
{
    reg.register_component<component::image>();
    reg.register_component<component::position>();
    reg.register_component<component::draw>();
    reg.register_component<component::rect>();
    reg.register_component<component::interaction>();
    reg.register_component<component::animation>();
}