/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#ifdef _WIN32
#include "../../framework.h"
#endif

#include "../../include/headers.hpp"
#include <asio.hpp>
#include <algorithm>
#include <thread>
#include <vector>
#include <cstdint>
#include <cstring>

void launch_tcp_server();
void launch_udp_server();

class Server {
    public : 
        Server() {};
        ~Server() {};
        void add_client(uint16_t id) {
            _clients_id.push_back(id);
        };
        void remove_client(uint16_t id) {
            _clients_id.erase(std::remove(_clients_id.begin(), _clients_id.end(), id), _clients_id.end());
        };
        std::vector<uint16_t> get_clients_id() {
            return _clients_id;
        };
    private :
        std::vector<uint16_t> _clients_id;
        bool in_game = false;
};

#endif /* !SERVER_HPP_ */
