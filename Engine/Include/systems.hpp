/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** systemes
*/

#ifndef SYSTEMES_HPP_
#define SYSTEMES_HPP_

#include "registry.hpp"
#include "draw.hpp"
#include "image.hpp"
#include "position.hpp"


//system
void draw_system(registry &reg, sparse_array<component::draw> &draw, sparse_array<component::image> &image);
void position_system(registry &reg, sparse_array<component::position> &position, sparse_array<component::image> &image);
//

// load ECS
void load_component(registry &reg);
void load_system(registry &reg);
//


#endif /* !SYSTEMES_HPP_ */
