/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** interaction
*/


#include "interaction.hpp"

component::interaction::interaction()
{
}

component::interaction::~interaction()
{
}

bool component::interaction::type_is_register(std::uint8_t type) const noexcept
{
    return _handling.find(type) != _handling.end();
}

void component::interaction::new_interaction(std::uint8_t type, const component::interaction::interaction_function &fun) noexcept
{
    _handling[type] = fun;
}

void component::interaction::trigger_interaction(std::uint8_t type, entity_t &e, registry &reg) const
{
    if (type_is_register(type) == false)
        throw std::runtime_error("error type is not in the list of interaction");
    _handling.at(type)(e, reg);
}

void component::interaction::delete_interaction(std::uint8_t type)
{
    if (type_is_register(type) == false)
        throw std::runtime_error("error type is not in the list of interaction");
    _handling.erase(type);
}