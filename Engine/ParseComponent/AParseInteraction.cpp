/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** AParseInteraction
*/

#include "AParseInteraction.hpp"

AParseInteraction::AParseInteraction()
{
}

AParseInteraction::~AParseInteraction()
{
}

void AParseInteraction::set_interaction(handling_interaction &interaction) noexcept
{
    _interaction = &interaction;
}

handling_interaction const *AParseInteraction::get_interaction() noexcept
{
    return _interaction;
}