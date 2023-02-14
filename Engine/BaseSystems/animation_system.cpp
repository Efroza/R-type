/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** animation_system
*/

#include "registry.hpp"
#include "rect.hpp"
#include "animation.hpp"
#include "image.hpp"

void animation_system(registry &reg
,sparse_array<component::image> &images, sparse_array<component::rect> &rects, sparse_array<component::animation> &animations)
{
    for (std::uint32_t i = 0; i < rects.size() && i < animations.size() && i < images.size(); ++i) {
        if (!rects[i] || !animations[i] || !images[i])
            continue;
        if (animations[i].value().time > 0) {
            animations[i].value().time -= 1;
            continue;
        }
        rects[i].value().animation();
        sf::IntRect &rect = rects[i].value().getRect();
        animations[i].value().time = animations[i].value().origin_time;
        images[i].value().get_sprite().setTextureRect(rect);
    }
}