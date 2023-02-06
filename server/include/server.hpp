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

#include <iostream>
#include <asio.hpp>
#include <thread>
#include <vector>

void launch_tcp_server();
void launch_udp_server();

#endif /* !SERVER_HPP_ */
