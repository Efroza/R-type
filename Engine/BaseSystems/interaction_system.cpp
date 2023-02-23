/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** interaction_system
*/

#include "registry.hpp"
#include "interaction.hpp"

// static void handling_type(sf::Event::EventType type, std::uint8_t id, registry &reg, component::interaction const &interaction)
// {

//     if (interaction.type_is_register(type) == false)
//         return;
//     entity_t e(id);
//     interaction.trigger_interaction(type, e, reg);
// }

// static void handling_code(sf::Keyboard::Key code, std::uint8_t id, registry &reg, component::interaction const &interaction)
// {
//     if (interaction.type_is_register(code) == false)
//         return;
//     entity_t e(id);
//     interaction.trigger_interaction(code, e, reg);
// }

static void handling_typing(std::uint8_t code, std::uint8_t id, registry &reg, component::interaction const &interaction)
{
    if (interaction.type_is_register(code) == false)
        return;
    entity_t e(id);
    interaction.trigger_interaction(code, e, reg);
}

void interaction_system(registry &reg, sparse_array<component::interaction> &interactions)
{
    sf::RenderWindow &window = reg.get_window();

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

// void interaction_system(registry &reg, sparse_array<component::interaction> &interactions)
// {
//     sf::RenderWindow &window = reg.get_window();
//     sf::Event event;

//     while (window.pollEvent(event)) {
//         if (event.type == sf::Event::Closed) {
//             window.close();
//             return;
//         }
//         for (std::uint32_t i = 0; i < interactions.size(); ++i) {
//             if (!interactions[i])
//                 continue;
//             handling_type(event.type, i, reg, interactions[i].value());
//             if (event.type == sf::Event::KeyPressed)
//                 handling_code(event.key.code, i, reg, interactions[i].value());
//         }
//     }
// }