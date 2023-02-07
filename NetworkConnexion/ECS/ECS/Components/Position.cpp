/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Position
*/

#include "Position.hpp"

Position::Position(int x = 0, int y = 0) : AComponent(POSITION), _position({x, y})
{
}

Position::~Position()
{
}

void Position::setXPosition(int x)
{
    _position.first = x;
}

void Position::setYPosition(int y)
{
    _position.second = y;
}

void Position::setPosition(int x, int y)
{
    _position = {x, y};
}

std::pair<int, int> const &Position::getPosition()
{
    return _position;
}


