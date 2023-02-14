/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** rect
*/

#ifndef RECT_HPP_
#define RECT_HPP_

#include <cinttypes>
#include <SFML/Graphics.hpp>

namespace component
{
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
            void set_size(int_size size_widht, int_size size_height) noexcept;
            bool size_is_set() const noexcept;
            int_size get_cols() const noexcept;
            int_size get_lines() const noexcept;
            void select_row(int_size row) noexcept;
            void select_col(int_size col) noexcept;
            void animation() noexcept;
            sf::IntRect &getRect() noexcept;
            void update() noexcept;

        private:
            int_size _lines;
            int_size _cols;
            int_size _size_width;
            int_size _size_height;
            int_size _row;
            int_size _col;
            sf::IntRect _rect;
        public:
            int_size marge_x;
            int_size marge_y;
    };
}


#endif /* !RECT_HPP_ */