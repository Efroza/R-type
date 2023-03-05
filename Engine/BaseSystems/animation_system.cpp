/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** animation_system
*/

#include "../Include/registry.hpp"
#include "../BaseComponent/rect.hpp"
#include "../BaseComponent/animation.hpp"
#include "../BaseComponent/image.hpp"

/**
 * @file animation_system.cpp
 */

/**
 * @brief Updates the animation system by processing all relevant image, rectangle, and animation components.
 *
 * @param reg The registry containing all entities and their associated components.
 * @param images The sparse array of image components.
 * @param rects The sparse array of rectangle components.
 * @param animations The sparse array of animation components.
 */
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
        animations[i].value().time = animations[i].value().origin_time;
    }
}