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

#include "../../shared/include/headers.hpp"
#include "../../shared/include/ClientInfo.hpp"

void launch_tcp_server();
void launch_udp_server();

class Server {
    public:
        Server();
        ~Server();


        // Handle list of clients
        void add_client(uint16_t id, std::shared_ptr<asio::ip::tcp::socket> socket);
        ClientInfo* get_client_info(uint16_t client_id) const;
        void remove_client(uint16_t client_id);
        uint16_t get_nb_clients() const;
        void print_all_clients() const;
        void new_client(uint16_t client_id);

    private:
        std::map<uint16_t, ClientInfo*> client_info_map;
};

#endif /* !SERVER_HPP_ */
