/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** down_deplacement
*/

#include "registry.hpp"
#include "position.hpp"
#include "down_deplacement.hpp"

extern "C" ILoad_Interaction *createInteraction()
{
    return new down_deplacement;
}

void down_deplacement_function(entity_t &e, registry &reg)
{
    sparse_array<component::position> &all_pos = reg.get_components<component::position>();
    auto &maybe_pos = all_pos[e];
    if (!maybe_pos)
        return;
    component::position &pos = maybe_pos.value();
    pos.y += 20;
}

down_deplacement::down_deplacement()
    : name("down_deplacement"), function(down_deplacement_function)
{
}

down_deplacement::~down_deplacement()
{
}

std::string down_deplacement::get_name() const noexcept
{
    return name;
}

ILoad_Interaction::interaction_function const &down_deplacement::get_function() const noexcept
{
    return function;
}