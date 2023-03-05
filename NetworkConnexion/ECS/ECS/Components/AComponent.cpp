/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** AComponent
*/

#include "AComponent.hpp"

AComponent::AComponent(ComponentType type) : _type(type)
{
}

ComponentType const &AComponent::getType() const
{
    return this->_type;
}

