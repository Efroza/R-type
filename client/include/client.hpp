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

void async_tcp_client(const std::string& host, const std::string& port);
void async_udp_client(const std::string& host, const std::string& port);

// class Client {
//     public :
//         Client();
//         ~Client();

//         void launch_tcp_client();
//         void launch_udp_client();
//         void send_tcp_client(Header_client header, asio::ip::tcp::socket &socket, std::string message);
//         void receive_tcp_client(Header_server header, asio::ip::tcp::socket &socket);
//         void send_udp_client(Header_client header, asio::ip::udp::socket &socket, std::string message);
//         void receive_udp_client(Header_server header, asio::ip::udp::socket &socket);
//     private :
//         ClientInfo _client_info;
//         std::thread _start;
//         bool _lobby = false;
//         bool _in_game = false;
//         std::map<uint16_t, ClientInfo*> _other_clients;

// }
#endif /* !CLIENT_HPP_ */
