/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** newtork_sytem
*/

#include "../Include/registry.hpp"
#include "../BaseComponent/position.hpp"
#include "../BaseComponent/network.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void network_position_system(registry &reg, sparse_array<component::position> &positions, sparse_array<component::network> &network)
{
    for (size_t i = 0; i < positions.size() && i < network.size(); ++i)
    {
        if (positions[i] && network[i]) {
            // std::cout << '[' << positions[i].value().x << "][" << positions[i].value().y << "]" << std::endl;
            // sleep(1);
        }
    }
}