/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** image
*/

#include "image.hpp"

component::image::image(const std::string &file, data &db, entity_t const &e)
: name_file(file)
, db(&db)
, id(e._id)
{
}

component::image::image(const std::string &file, data &db)
: name_file(file)
, db(&db)
, id(db.new_id<sf::Texture>())
{
}

component::image::~image()
{
}

std::string const &component::image::get_name_file() const noexcept
{
    return name_file;
}

data *component::image::get_databases() noexcept
{
    return this->db;
}