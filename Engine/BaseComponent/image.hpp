/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

namespace component
{
    class image
    {
        public:
            image(const std::string &file);
            image(const image &move);
            ~image();
            sf::Sprite &get_sprite();

        private:
            void load_texture(const std::string &file);
        private:
            sf::Texture texture;
            sf::Sprite sprite;
    };

} // namespace component

#endif /* !IMAGE_HPP_ */