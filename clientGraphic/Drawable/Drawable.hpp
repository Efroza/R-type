/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Drawable
*/




#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <string>
#include <utility>

/**
 * @file Drawable.hpp
 */

enum colors_e {
    NO_COLOR,
    WHITE,
    BLACK,
    GREEN,
    RED,
    BLUE,
    CYAN,
    MAGENTA,
    YELLOW
};

/**
 * @brief Class that represent a drawable object.
 */
class Drawable
{
public:
    Drawable(const std::string &name, const std::string &str, const std::pair<int, int> &rect, const std::pair<int, int> position, bool isText = false, colors_e color = colors_e::WHITE);
    ~Drawable();

    const std::string &getName() const;

    const std::string &getStr() const;
    void setStr(const std::string &str);

    bool isText() const;
    std::pair<int, int> getRect() const;
    void setRect(const std::pair<int, int> &newRect);
    std::pair<int, int> getPosition() const;
    void setPosition(const std::pair<int, int> &newPosition);
    colors_e getColor() const;
    void setColor(colors_e color);

private:
    std::string _name;
    std::string _str;
    std::pair<int, int> _rect;
    std::pair<int, int> _pos;
    colors_e _color;
    bool _isText;
};


#endif