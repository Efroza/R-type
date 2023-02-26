/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** AGraphic
*/



#include "AGraphic.hpp"

AGraphic::AGraphic(const std::string &name) : _graphLib(name)
{
}

const std::string &AGraphic::getName() const
{
    return this->_graphLib;
}