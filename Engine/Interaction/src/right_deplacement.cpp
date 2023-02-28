/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** right_deplacement
*/

#include "registry.hpp"
#include "position.hpp"
#include "right_deplacement.hpp"

extern "C" ILoad_Interaction *createInteraction()
{
    return new right_deplacement;
}

void right_deplacement_function(entity_t &e, registry &reg)
{
    sparse_array<component::position> &all_pos = reg.get_components<component::position>();
    auto &maybe_pos = all_pos[e];
    if (!maybe_pos)
        return;
    component::position &pos = maybe_pos.value();
    pos.x += 20;
}

right_deplacement::right_deplacement()
    : name("right_deplacement"), function(right_deplacement_function)
{
}

right_deplacement::~right_deplacement()
{
}

std::string right_deplacement::get_name() const noexcept
{
    return name;
}

ILoad_Interaction::interaction_function const &right_deplacement::get_function() const noexcept
{
    return function;
}