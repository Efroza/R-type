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
#include "../Include/data.hpp"
#include "../Include/entity.hpp"

/**
 * @file image.hpp
*/

namespace component
{
    /**
     * @brief This class is used to create a image.
     */
    class image
    {
        public:
            image(const std::string &file, data &db, entity_t const &e);
            image(const std::string &file, data &db);
            ~image();
            std::string const &get_name_file() const noexcept;
            data *get_databases() noexcept;

        private:
        public:
            std::string name_file;
            data *db;
            size_t id;
    };

} // namespace component

#endif /* !IMAGE_HPP_ */