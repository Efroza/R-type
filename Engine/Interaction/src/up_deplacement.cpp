/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** up_deplacement
*/

#include "../../Include/registry.hpp"
#include "../../BaseComponent/position.hpp"
#include "../Include/up_deplacement.hpp"

/**
 * @file up_deplacement.cpp
 */

/**
 * @brief Create a Interaction object
 *
 * @return ILoad_Interaction*
 * @details This function is called by the plugin loader to create a new instance of the plugin
 */
#ifdef _WIN32
extern "C" __declspec(dllexport) ILoad_Interaction *createInteraction()
{
    return new up_deplacement;
}
#else
extern "C" ILoad_Interaction *createInteraction()
{
    return new up_deplacement;
}
#endif

/**
 * @brief Function called when the interaction is triggered
 *
 * @param e The entity that triggered the interaction
 * @param reg The registry of the game
 * @details This function will make the entity move up by 20 pixels
 */

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

/**
 * @brief Get the Name object
 *
 * @return std::string
 * @details This function will return the name of the interaction
 */

std::string up_deplacement::get_name() const noexcept
{
    return name;
}

/**
 * @brief Get the Function object
 *
 * @return ILoad_Interaction::interaction_function
 * @details This function will return the function of the interaction
 */

ILoad_Interaction::interaction_function const &up_deplacement::get_function() const noexcept
{
    return function;
}