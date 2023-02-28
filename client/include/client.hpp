/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#ifdef _WIN32
#include "../../framework.h"
#endif

#include "../../shared/include/headers.hpp"
#include "../../shared/include/ClientInfo.hpp"
#include <asio.hpp>
#include <thread>
#include <cstdint>
#include <array>

using asio::ip::tcp;
using asio::ip::udp;

void async_udp_client(const std::string& host, const std::string& port);

class Client {
    public :
        Client(const std::string& host, const std::string& port);
        ~Client();

        void async_tcp_client(const asio::error_code& ec);
        void connect_to_server(const asio::error_code& ec);
        void inGame();
        void inLobby();
        void send_tcp_client(Header_client header, std::string message);
        void receive_tcp_client(Header_server header);
        void start_game(Header_server header);
        void launch_game();

    private :
        ClientInfo _client_info;
        bool _lobby_created = false;
        bool _in_game = false;
        std::shared_ptr<tcp::socket> _socket;
        uint16_t _id = 0;
        std::vector<ClientInfo*> _other_clients;
};
#endif /* !CLIENT_HPP_ */
