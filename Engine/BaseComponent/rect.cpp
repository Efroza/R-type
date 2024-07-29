/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** rect
*/

#include "rect.hpp"

/**
 * @file rect.cpp
 */

/**
 * @brief Construct a new component::rect::rect object
 *
 * @param line The number of lines.
 * @param cols The number of columns.
 * @details The entity will be associated with a given rect or not depending on the number of lines and columns.
 * @details If the number of lines and columns is 0, the entity will not be associated with a rect.
 * @details If the number of lines and columns is not 0, the entity will be associated with a rect to be able to possibibly get an animation or other actions on it.
 */

component::rect::rect(int_size line, int_size cols)
: _lines(line)
, _cols(cols)
, _size_width(0)
, _size_height(0)
, _row(0)
, _col(0)
, marge_x(0)
, marge_y(0)
, width(0)
, height(0)
, top(0)
, left(0)
{

}

/**
 * @brief Construct a new component::rect::rect object
 *
 * @param line The number of lines.
 * @param cols The number of columns.
 * @param size_width The width of the rect.
 * @param size_height The height of the rect.
 * @details The entity will be associated with a given rect or not depending on the number of lines and columns.
 * @details If the number of lines and columns is 0, the entity will not be associated with a rect.
 * @details If the number of lines and columns is not 0, the entity will be associated with a rect to be able to possibibly get an animation or other actions on it.
 */

component::rect::rect(int_size line, int_size cols, int_size size_width, int_size size_height)
: _lines(line)
, _cols(cols)
, _size_width(size_width)
, _size_height(size_height)
, _row(0)
, _col(0)
, marge_x(0)
, marge_y(0)
, width(0)
, height(0)
, top(0)
, left(0)
{

}

component::rect::~rect()
{

}

/**
 * @brief Set the cols object
 *
 * @param cols The number of columns.
 * @details The number of columns will be reset if not already set in the constructor.
 */

void component::rect::set_cols(int_size cols) noexcept
{
    _cols = cols;
}

/**
 * @brief Set the lines object
 *
 * @param lines The number of lines.
 * @details The number of lines will be reset if not already set in the constructor.
 */

void component::rect::set_lines(int_size lines) noexcept
{
    _lines = lines;
}

// void component::rect::set_size(int_size size_width, int_size size_height) noexcept
// {
//     _size_width = size_width;
//     _size_height = size_height;
//     if (_size_height == 0 || _size_width == 0 || _lines == 0 || _cols == 0)
//         return;
//     width = _size_width / _cols;
//     height = _size_height / _lines;
// }

/**
 * @brief Return the number of columns.
 *
 * @return component::rect::int_size
 * @details If the number of columns is not set, it will return 0.
 */

component::rect::int_size component::rect::get_cols() const noexcept
{
    return _cols;
}

/**
 * @brief Return the number of lines.
 *
 * @return component::rect::int_size
 * @details If the number of lines is not set, it will return 0.
 */

component::rect::int_size component::rect::get_lines() const noexcept
{
    return _lines;
}

/**
 * @brief Return the width of the rect.
 *
 * @return component::rect::int_size
 * @details It will return the width of the rect in relation of the entire size of the entity.
 */

void component::rect::select_row(int_size row) noexcept
{
    if (row > _lines)
        return;
    _row = row;
    if (_size_height == 0 || _size_width == 0 || _lines == 0)
        return;
    top = row * (_size_height / _lines) + marge_y;
}

/**
 * @brief Return the height of the rect.
 *
 * @return component::rect::int_size
 * @details It will return the height of the rect in relation of the entire size of the entity.
 */

void component::rect::select_col(int_size col) noexcept
{
    if (col > _cols)
        return;
    _col = col;
    if (_size_height == 0 || _size_width == 0 || _cols == 0)
        return;
    left = _col * (_size_width / _cols) + marge_x;
}

/**
 * @brief This function will be used to do the animation of our image given to the entity.
 *
 * @details It will be used to do the animation of our image given to the entity.
 * @details This function will be able to do it thanks to the number of lines and columns, aka the rect.
 */
void component::rect::animation() noexcept
{
    if (_size_height == 0 || _size_width == 0 || _lines == 0 || _cols == 0)
        return;
    if (left + (_size_width / _cols) >= _size_width) {
        left = _col * (_size_width / _cols);
    }
    else
        left += (_size_width / _cols);
    if (top + (_size_height / _lines) == height)
        top = _row * (_size_height / _lines);
    else
    top += (_size_height / _lines);
}

/**
 * @brief Will tell if the size of the rect is set.
 *
 * @return true
 * @return false
 */

bool component::rect::size_is_set() const noexcept
{
    return _size_height != 0 && _size_width != 0;
}

// void component::rect::update() noexcept
// {
//     if (_cols)
//         left = _col * (_size_width / _cols) + marge_x;
//     if (_lines)
//         top = _row * (_size_height / _lines) + marge_y;
// }