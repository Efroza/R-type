/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** newtork_sytem
*/

#include "../Include/networks.hpp"
#include "../Include/registry.hpp"
#include "../BaseComponent/position.hpp"

void network_position_system(registry &reg, sparse_array<component::position> &positions, sparse_array<component::network> &network)
{
    for (size_t i = 0; i < positions.size() && i < network.size(); ++i) {
        if (positions[i] && network[i])
            std::cout << '[' << positions[i].value().x << "][" << positions[i].value().y << "]" << std::endl;
    }
}