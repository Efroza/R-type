/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** interaction_system
*/

#include "registry.hpp"
#include "interaction.hpp"

static void handling_typing(std::uint8_t code, std::uint8_t id, registry &reg, component::interaction const &interaction)
{
    if (interaction.type_is_register(code) == false)
        return;
    entity_t e(id);
    interaction.trigger_interaction(code, e, reg);
}

void interaction_system(registry &reg, sparse_array<component::interaction> &interactions)
{

    for (std::uint32_t i = 0; i < interactions.size(); ++i)
    {
        if (!interactions[i])
            continue;
        for (auto &typing : interactions[i].value().get_typing()) {
            handling_typing(typing, i, reg, interactions[i].value());
        }
        interactions[i].value().empty_typing();
    }
}