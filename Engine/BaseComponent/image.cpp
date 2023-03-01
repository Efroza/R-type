/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** image
*/

#include "image.hpp"

/**
 * @file image.cpp
 */

/**
 * @brief Construct a new component::image::image object
 *
 * @param file The file path of the image.
 * @param db Represent the data object for storing the image data.
 * @param e The entity that will be associated with the image.
 * @details The entity will be associated with a given image and will be able to use it.
 */

component::image::image(const std::string &file, data &db, entity_t const &e)
: name_file(file)
, db(&db)
, id(e._id)
{
}

/**
 * @brief Construct a new component::image::image object
 *
 * @param file The file path of the image.
 * @param db Represent the data object for storing the image data.
 * @details The entity will be associated with a given image and will be able to use it.
 */

component::image::image(const std::string &file, data &db)
: name_file(file)
, db(&db)
, id(db.new_id<sf::Texture>())
{
}

/**
 * @brief Destroy the component::image::image object
 *
 * @details The image will be deleted from the data object and the entity will no longer be associated with it.
 */
component::image::~image()
{
}

/**
 * @brief Get the name file object
 *
 * @return std::string const& The file path of the image.
 * @details The file path of the image will be returned.
 */

std::string const &component::image::get_name_file() const noexcept
{
    return name_file;
}

/**
 * @brief Get the id object
 *
 * @return entity_t const& The id of the entity associated with the image.
 * @details The id of the entity associated with the image will be returned.
 */

data *component::image::get_databases() noexcept
{
    return this->db;
}