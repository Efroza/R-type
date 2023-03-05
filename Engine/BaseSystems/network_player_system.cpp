/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** network_player_system
*/

#include "../Include/registry.hpp"
#include "../BaseComponent/position.hpp"
#include "../BaseComponent/network_player.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void network_player_system(registry &reg, sparse_array<component::position> &positions, sparse_array<component::network_player> &network)
{
    Position position = {0};

    for (size_t i = 0; i < positions.size() && i < network.size(); ++i)
    {
        if (positions[i] && network[i])
        {
            std::uint16_t client_id = network[i].value().client_id;
            UDP_Server *server = network[i].value().server;
            if (server == nullptr || client_id == 0)
                continue;
            position.x = positions[i].value().x;
            position.y = positions[i].value().y;
            server->send_position(client_id, position);
            #ifdef _WIN32
            Sleep(1);
            #else
            sleep(1);
            #endif
        }
    }
}