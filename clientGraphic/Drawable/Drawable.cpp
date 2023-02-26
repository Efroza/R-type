/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Drawable
*/



#include "Drawable.hpp"


Drawable::Drawable(const std::string &str, const std::pair<int, int> &rect, bool isText) : _str(str), _rect(rect), _isText(isText)
{
}

Drawable::~Drawable()
{
}

const std::string &Drawable::getStr() const
{
    return this->_str;
}

bool Drawable::isText() const
{
    return this->_isText;
}

std::pair<int, int> Drawable::getRect() const
{
    return this->_rect;
}


