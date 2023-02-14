/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** up_deplacement
*/

#include "registry.hpp"
#include "position.hpp"

void up_deplacement(entity_t e, registry &reg)
{
    sparse_array<component::position> &all_pos = reg.get_components<component::position>();
    auto &maybe_pos = all_pos[e];
    if (!maybe_pos)
        return;
    component::position &pos = maybe_pos.value();
    pos.pos.y -= 20;
}