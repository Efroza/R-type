/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** rect_system
*/

#include "registry.hpp"
#include "image.hpp"
#include "rect.hpp"

void set_rect_system(registry &reg, sparse_array<component::image> &images, sparse_array<component::rect> &rect)
{
    for (std::uint32_t i = 0; i < images.size() && i < rect.size(); ++i) {
        if (!images[i] || !rect[i] || rect[i].value().size_is_set() == true)
            continue;
        // sf::Texture &texture = images[i].value().get_texture();
        // rect[i].value().set_size(texture.getSize().x, texture.getSize().y);
        // rect[i].value().update();
        // sf::IntRect &res = rect[i].value().getRect();
        // images[i].value().get_sprite().setTextureRect(res);
    }
}