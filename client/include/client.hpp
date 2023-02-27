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
#include <asio.hpp>
#include <thread>
#include <cstdint>
#include <array>

using asio::ip::tcp;
using asio::ip::udp;

void async_tcp_client(const std::string& host, const std::string& port);
void async_udp_client(const std::string& host, const std::string& port);

#endif /* !CLIENT_HPP_ */
