/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** interaction
*/


#include "interaction.hpp"

/**
 * @file interaction.cpp
 */

component::interaction::interaction()
{
}

component::interaction::~interaction()
{
}

/**
 * @brief Check if the type is register
 *
 * @param type The type of the interaction.
 * @return true The type is register.
 * @return false The type is not register.
 * @details The type will be checked if it is in the list of interaction.
 */

bool component::interaction::type_is_register(std::uint8_t type) const noexcept
{
    return _handling.find(type) != _handling.end();
}

/**
 * @brief Register a new interaction
 *
 * @param type The type of the interaction.
 * @param fun The function that will be called when the interaction is triggered.
 * @details The type will be register and the function will be called when the interaction is triggered.
 */

void component::interaction::new_interaction(std::uint8_t type, const component::interaction::interaction_function &fun) noexcept
{
    _handling[type] = fun;
}

/**
 * @brief Trigger the interaction
 *
 * @param type The type of the interaction.
 * @param e The entity that will be associated with the interaction.
 * @param reg The registry that will be associated with the interaction.
 * @details The interaction will be triggered and the function will be called.
 */

void component::interaction::trigger_interaction(std::uint8_t type, entity_t &e, registry &reg) const
{
    if (type_is_register(type) == false)
        throw std::runtime_error("error type is not in the list of interaction");
    _handling.at(type)(e, reg);
}

/**
 * @brief Delete the interaction
 *
 * @param type The type of the interaction.
 * @details The interaction will be deleted.
 */

void component::interaction::delete_interaction(std::uint8_t type)
{
    if (type_is_register(type) == false)
        throw std::runtime_error("error type is not in the list of interaction");
    _handling.erase(type);
}

/**
 * @brief Get the interaction object
 *
 * @param type The type of the interaction.
 * @return component::interaction::interaction_function const& The function that will be called when the interaction is triggered.
 * @details The function will be returned.
 */

void component::interaction::set_typing(std::uint8_t type) noexcept
{
    typing.emplace_back(type);
}

/**
 * @brief Get the typing object
 *
 * @return std::vector<std::uint8_t> const& The typing.
 * @details The typing will be returned.
 */

std::vector<std::uint8_t> const &component::interaction::get_typing() const noexcept
{
    return typing;
}

/**
 * @brief Empty the typing
 *
 * @details The typing will be set to 0.
 */

void component::interaction::empty_typing() noexcept
{
    typing.resize(0);
}
