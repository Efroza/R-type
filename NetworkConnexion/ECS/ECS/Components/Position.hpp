/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Position
*/

#ifndef POSITION_HPP

#include <utility>
#include "AComponent.hpp"

class Position : AComponent
{
public:
    Position(int x, int y);
    ~Position();

    void setXPosition(int x) noexcept;
    void setYPosition(int y) noexcept;
    void setPosition(int x, int y) noexcept;
    std::pair<int, int> const &getPosition() noexcept;
private:
    std::pair<int, int> _position;
};


#endif