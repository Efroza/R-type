/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** left_deplacement
*/

#include "registry.hpp"
#include "position.hpp"
#include "left_deplacement.hpp"

extern "C" ILoad_Interaction *createInteraction()
{
    return new left_deplacement;
}

void left_deplacement_function(entity_t &e, registry &reg)
{
    sparse_array<component::position> &all_pos = reg.get_components<component::position>();
    auto &maybe_pos = all_pos[e];
    if (!maybe_pos)
        return;
    component::position &pos = maybe_pos.value();
    pos.x -= 20;
}

left_deplacement::left_deplacement()
    : name("left_deplacement"), function(left_deplacement_function)
{
}

left_deplacement::~left_deplacement()
{
}

std::string left_deplacement::get_name() const noexcept
{
    return name;
}

ILoad_Interaction::interaction_function const &left_deplacement::get_function() const noexcept
{
    return function;
}