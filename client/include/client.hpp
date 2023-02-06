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

#include <iostream>
#include <asio.hpp>
#include <thread>
#include <cstdint>
#include <array>

using asio::ip::tcp;
using asio::ip::udp;

void async_tcp_client(const std::string& host, const std::string& port);
void async_udp_client(const std::string& host, const std::string& port);
// class TcpClient
// {
// public:
//     TcpClient(asio::io_context& io_context, const std::string& host, const std::string& port)
//         : socket_(io_context)
//     {
//         asio::error_code ec;
//         tcp::resolver resolver(io_context);
//         auto endpoints = resolver.resolve(host, port, ec);
//         if (ec)
//         {
//             throw std::runtime_error("Error resolving host: " + ec.message());
//         }

//         asio::connect(socket_, endpoints, ec);
//         if (ec)
//         {
//             throw std::runtime_error("Error connecting to host: " + ec.message());
//         }
//     }

//     void send(const std::string& message)
//     {
//         asio::error_code ec;
//         asio::write(socket_, asio::buffer(message), ec);
//         if (ec)
//         {
//             throw std::runtime_error("Error sending message: " + ec.message());
//         }
//     }

// private:
//     tcp::socket socket_;
// };

// class UdpClient
// {
// public:
//     UdpClient(asio::io_context& io_context, const std::string& host, const std::string& port)
//         : socket_(io_context, udp::endpoint(udp::v4(), 0)),
//           endpoint_(*resolver_.resolve(udp::v4(), host, port).begin())
//     {
//     }

//     void send(const std::string& message)
//     {
//         asio::error_code ec;
//         socket_.send_to(asio::buffer(message), endpoint_, 0, ec);
//         if (ec)
//         {
//             throw std::runtime_error("Error sending message: " + ec.message());
//         }
//     }

// private:
//     udp::socket socket_;
//     udp::resolver resolver_;
//     udp::endpoint endpoint_;
// };

#endif /* !CLIENT_HPP_ */
