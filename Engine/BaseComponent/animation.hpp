/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** animation
*/

#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include <cinttypes>

namespace component {
    struct animation {
        animation(std::uint32_t new_time = 0) : time(new_time), origin_time(new_time) {}
        std::uint32_t time;
        std::uint32_t origin_time;
    };
}
#endif /* !ANIMATION_HPP_ */
