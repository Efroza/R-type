/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** image
*/

#include "image.hpp"

component::image::image(const std::string &file)
{
    load_texture(file);
    sprite.setTexture(texture);
}

component::image::image(const component::image &copy)
{
    texture = copy.texture;
    sprite = copy.sprite;
}

component::image::~image()
{
}

void component::image::load_texture(const std::string &file)
{
    if (!texture.loadFromFile(file))
        throw std::runtime_error("error load file " + file + " into texture");
    texture.setSmooth(true);
}

sf::Sprite &component::image::get_sprite()
{
    return sprite;
}