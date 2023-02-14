/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** image
*/

#include "image.hpp"

component::image::image(const std::string &file, data &db, entity_t const &e) : db(&db), id(e._id)
{
    load_texture(file);
    sf::Texture &texture = db.get_data<sf::Texture>(id);
    sprite.setTexture(texture);
}

component::image::image(const std::string &file, data &db) : db(&db), id(db.new_id<sf::Texture>())
{
    load_texture(file);
    sf::Texture &texture = db.get_data<sf::Texture>(id);
    sprite.setTexture(texture);
}

component::image::image(component::image const &copy)
: db(copy.db), id(copy.id), sprite(copy.sprite)
{
}

component::image::~image()
{
}

void component::image::load_texture(const std::string &file)
{
    sf::Texture texture;
    if (!texture.loadFromFile(file))
        throw std::runtime_error("error load file " + file + " into texture");
    texture.setSmooth(true);
    db->insert_data<sf::Texture>(std::move(texture), id);
}

sf::Sprite &component::image::get_sprite()
{
    return sprite;
}

sf::Texture &component::image::get_texture() const noexcept
{
    return db->get_data<sf::Texture>(id);
}