/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** left_deplacement
*/

#include "registry.hpp"
#include "position.hpp"
#include "left_deplacement.hpp"

/**
 * @brief Create a Interaction object
 *
 * @return ILoad_Interaction*
 * @details This function is called by the plugin loader to create a new instance of the plugin
 */
extern "C" ILoad_Interaction *createInteraction()
{
    return new left_deplacement;
}

/**
 * @brief Function called when the interaction is triggered
 *
 * @param e The entity that triggered the interaction
 * @param reg The registry of the game
 * @details This function will make the entity move left by 20 pixels
 */
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

/**
 * @brief Get the Name object
 *
 * @return std::string
 * @details This function will return the name of the interaction
 */
std::string left_deplacement::get_name() const noexcept
{
    return name;
}

/**
 * @brief Get the Function object
 *
 * @return ILoad_Interaction::interaction_function const&
 * @details This function will return the function of the interaction
 */
ILoad_Interaction::interaction_function const &left_deplacement::get_function() const noexcept
{
    return function;
}