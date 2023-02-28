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
, marge_x(0)
, marge_y(0)
, width(0)
, height(0)
, top(0)
, left(0)
{

}

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

void component::rect::set_cols(int_size cols) noexcept
{
    _cols = cols;
}

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
    top = row * (_size_height / _lines) + marge_y;
}

void component::rect::select_col(int_size col) noexcept
{
    if (col > _cols)
        return;
    _col = col;
    if (_size_height == 0 || _size_width == 0 || _cols == 0)
        return;
    left = _col * (_size_width / _cols) + marge_x;
}


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