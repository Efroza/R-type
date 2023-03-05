/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** interaction_system
*/

#include "../Include/registry.hpp"
#include "../BaseComponent/interaction.hpp"

/**
 * @file interaction_system.cpp
 */

/**
 * @brief Handles typing input for the specified interaction component and triggers the corresponding interaction function.
 *
 * @param code The input code to handle.
 * @param id The ID of the entity associated with the interaction component.
 * @param reg The registry containing all entities and their associated components.
 * @param interaction The interaction component to handle.
 * @details This function is static and is only used by the interaction system since it is not meant to be used by other systems.
 */
static void handling_typing(std::uint8_t code, std::uint8_t id, registry &reg, component::interaction const &interaction)
{
    if (interaction.type_is_register(code) == false)
        return;
    entity_t e(id);
    interaction.trigger_interaction(code, e, reg);
}

/**
 * @brief Updates the interaction system by processing all relevant interaction components.
 *
 * @param reg The registry containing all entities and their associated components.
 * @param interactions The sparse array of interaction components.
 */
void interaction_system(registry &reg, sparse_array<component::interaction> &interactions)
{

    for (std::uint32_t i = 0; i < interactions.size(); ++i)
    {
        if (!interactions[i])
            continue;
        for (auto &typing : interactions[i].value().get_typing())
        {
            handling_typing(typing, i, reg, interactions[i].value());
        }
        interactions[i].value().empty_typing();
    }
}