/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** rect
*/

#ifndef RECT_HPP_
#define RECT_HPP_

#include <cinttypes>

/**
 * @file rect.hpp
*/

namespace component
{
    /**
     * @brief This class is used to create a rectangle.
    */
    class rect
    {
        public:
            using int_size = std::uint32_t;

        public:
            rect(int_size line, int_size cols);
            rect(int_size line, int_size cols, int_size size_width, int_size size_height);
            ~rect();
            void set_cols(int_size cols) noexcept;
            void set_lines(int_size lines) noexcept;
            void set_size(int_size size_widht, int_size size_height) noexcept
            {
                _size_height = size_height;
                _size_width = size_widht;
                if (_size_height == 0 || _size_width == 0 || _lines == 0 || _cols == 0)
                    return;
                width = _size_width / _cols;
                height = _size_height / _lines;
            }
            bool size_is_set() const noexcept;
            int_size get_cols() const noexcept;
            int_size get_lines() const noexcept;
            void select_row(int_size row) noexcept;
            void select_col(int_size col) noexcept;
            void animation() noexcept;
            void update() noexcept
            {
                if (_cols)
                    left = _col * (_size_width / _cols) + marge_x;
                if (_lines)
                    top = _row * (_size_height / _lines) + marge_y;
            }

        private:
            int_size _lines;
            int_size _cols;
            int_size _size_width;
            int_size _size_height;
            int_size _row;
            int_size _col;
        public:
            int_size marge_x;
            int_size marge_y;
        public:
            int_size width;
            int_size height;
            int_size top;
            int_size left;
    };
}


#endif /* !RECT_HPP_ */