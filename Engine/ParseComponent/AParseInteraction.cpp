/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** AParseInteraction
*/

#include "AParseInteraction.hpp"

/**
 * @file AParseInteraction.cpp
 *
 * @brief This file contains the implementation of the AParseInteraction class
 */

AParseInteraction::AParseInteraction()
{
}

AParseInteraction::~AParseInteraction()
{
}

/**
 * @brief Set the interaction object
 *
 * @param interaction interaction to set
 */

void AParseInteraction::set_interaction(handling_interaction &interaction) noexcept
{
    _interaction = &interaction;
}

/**
 * @brief Get the interaction object
 *
 * @return handling_interaction*
 */

handling_interaction const *AParseInteraction::get_interaction() noexcept
{
    return _interaction;
}