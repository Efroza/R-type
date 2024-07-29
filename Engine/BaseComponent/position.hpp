/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <SFML/Graphics.hpp>

namespace component {
    struct position
    {
        position(int x, int y) : x(x), y(y), pos(x, y) {}
        int x;
        int y;
        sf::Vector2f pos;
    };
}

#endif /* !POSITION_HPP_ */