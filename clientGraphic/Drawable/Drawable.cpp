/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Drawable
*/



#include "Drawable.hpp"


Drawable::Drawable(const std::string &name, const std::string &str, const std::pair<int, int> &rect, const std::pair<int, int> position, bool isText, colors_e color) : _name(name), _str(str), _rect(rect), _pos(position), _isText(isText), _color(color)
{
}

Drawable::~Drawable()
{
}

const std::string &Drawable::getName() const
{
    return this->_name;
}

const std::string &Drawable::getStr() const
{
    return this->_str;
}

void Drawable::setStr(const std::string &str)
{
    this->_str = str;
}

bool Drawable::isText() const
{
    return this->_isText;
}

std::pair<int, int> Drawable::getRect() const
{
    return this->_rect;
}

std::pair<int, int> Drawable::getPosition() const
{
    return this->_pos;
}

void Drawable::setPosition(const std::pair<int, int> &newPosition)
{
    this->_pos = newPosition;
}

colors_e Drawable::getColor() const
{
    return this->_color;
}

void Drawable::setColor(colors_e color)
{
    this->_color = color;
}

