/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** rect
*/

#include "rect.hpp"

component::rect::rect(int_size line, int_size cols)
: _lines(line)
, _cols(cols)
, _size_width(0)
, _size_height(0)
, _row(0)
, _col(0)
, _rect(0, 0, 0, 0)
, marge_x(0)
, marge_y(0)
{

}

component::rect::rect(int_size line, int_size cols, int_size size_width, int_size size_height)
: _lines(line)
, _cols(cols)
, _size_width(size_width)
, _size_height(size_height)
, _row(0)
, _col(0)
, _rect(0, 0, 0, 0)
, marge_x(0)
, marge_y(0)
{

}

component::rect::~rect()
{

}

void component::rect::set_cols(int_size cols) noexcept
{
    _cols = cols;
}

void component::rect::set_lines(int_size lines) noexcept
{
    _lines = lines;
}

void component::rect::set_size(int_size size_width, int_size size_height) noexcept
{
    _size_width = size_width;
    _size_height = size_height;
    if (_size_height == 0 || _size_width == 0 || _lines == 0 || _cols == 0)
        return;
    _rect.width = _size_width / _cols;
    _rect.height = _size_height / _lines;
}

component::rect::int_size component::rect::get_cols() const noexcept
{
    return _cols;
}

component::rect::int_size component::rect::get_lines() const noexcept
{
    return _lines;
}

void component::rect::select_row(int_size row) noexcept
{
    if (row > _lines)
        return;
    _row = row;
    if (_size_height == 0 || _size_width == 0 || _lines == 0)
        return;
    _rect.top = row * (_size_height / _lines) + marge_y;
}

void component::rect::select_col(int_size col) noexcept
{
    if (col > _cols)
        return;
    _col = col;
    if (_size_height == 0 || _size_width == 0 || _cols == 0)
        return;
    _rect.left = _col * (_size_width / _cols) + marge_x;
}

#include <iostream>

void component::rect::animation() noexcept
{
    if (_size_height == 0 || _size_width == 0 || _lines == 0 || _cols == 0)
        return;
    if (_rect.left + (_size_width / _cols) >= _size_width) {
        _rect.left = _col * (_size_width / _cols);
    }
    else
        _rect.left += (_size_width / _cols);
    if (_rect.top + (_size_height / _lines) == _rect.height)
        _rect.top = _row * (_size_height / _lines);
    else
    _rect.top += (_size_height / _lines);
}

sf::IntRect &component::rect::getRect() noexcept
{
    return _rect;
}

bool component::rect::size_is_set() const noexcept
{
    return _size_height != 0 && _size_width != 0;
}

void component::rect::update() noexcept
{
    if (_cols)
        _rect.left = _col * (_size_width / _cols) + marge_x;
    if (_lines)
        _rect.top = _row * (_size_height / _lines) + marge_y;
}