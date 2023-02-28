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
#include "rect.hpp"
#include "interaction.hpp"
#include "interactive.hpp"
#include "animation.hpp"
#include "collusion.hpp"
#include "network.hpp"

//system
void animation_system(registry &reg
,sparse_array<component::image> &images, sparse_array<component::rect> &rects, sparse_array<component::animation> &animations);
void interaction_system(registry &reg, sparse_array<component::interaction> &interactions);
void collusion_system(registry &reg, sparse_array<component::collusion> &collusion, sparse_array<component::image> &image);
void network_position_system(registry &reg, sparse_array<component::position> &positions, sparse_array<component::network> &network);
//

// load ECS
void load_component(registry &reg);
void load_system(registry &reg);
//


#endif /* !SYSTEMES_HPP_ */
