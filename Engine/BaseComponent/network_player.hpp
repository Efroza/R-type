/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** network_player
*/

#ifndef NETWORK_PLAYER_HPP_
#define NETWORK_PLAYER_HPP_

#include <cinttypes>
#include "../server/include/server.hpp"

namespace component
{
    class network_player
    {
        public:
            network_player(/* args */) : client_id(0), server(nullptr) {};
            ~network_player(){};
        public:
            std::uint16_t client_id;
            UDP_Server *server;
    };
} // namespace component


#endif /* !NETWORK_PLAYER_HPP_ */