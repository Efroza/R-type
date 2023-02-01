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
#include "data.hpp"
#include "entity.hpp"

namespace component
{
    class image
    {
        public:
            image(const std::string &file, data &db, entity_t const &e);
            image(image const &move);
            ~image();
            sf::Sprite &get_sprite();

        private:
            void load_texture(const std::string &file);
        private:
            sf::Sprite sprite;
            data *db;
            size_t id;
    };

} // namespace component

#endif /* !IMAGE_HPP_ */