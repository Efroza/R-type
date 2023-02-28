/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** up_deplacement
*/

#include "registry.hpp"
#include "position.hpp"
#include "up_deplacement.hpp"

extern "C" ILoad_Interaction *createInteraction()
{
    return new up_deplacement;
}

void up_deplacement_function(entity_t &e, registry &reg)
{
    sparse_array<component::position> &all_pos = reg.get_components<component::position>();
    auto &maybe_pos = all_pos[e];
    if (!maybe_pos)
        return;
    component::position &pos = maybe_pos.value();
    pos.y -= 20;
}

up_deplacement::up_deplacement()
: name("up_deplacement")
, function(up_deplacement_function)
{
}

up_deplacement::~up_deplacement()
{
}


std::string up_deplacement::get_name() const noexcept
{
    return name;
}

ILoad_Interaction::interaction_function const &up_deplacement::get_function() const noexcept
{
    return function;
}