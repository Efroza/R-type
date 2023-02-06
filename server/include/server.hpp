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
#include <algorithm>
#include <thread>
#include <vector>
#include <cstdint>
#include <cstring>

void launch_tcp_server();
void launch_udp_server();

// class TcpServer
// {
// public:
//     TcpServer(asio::io_context& io_context, short port)
//         : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
//     {
//         do_accept();
//     }

// private:
//     void do_accept()
//     {
//         acceptor_.async_accept(
//             [this](std::error_code ec, tcp::socket socket)
//             {
//                 if (!ec)
//                 {
//                     do_read(std::move(socket));
//                 }

//                 do_accept();
//             });
//     }

//     void do_read(tcp::socket socket)
//     {
//         asio::async_read(socket, asio::dynamic_buffer(data_),
//             [this, socket = std::move(socket)](std::error_code ec, size_t length)
//             {
//                 if (!ec)
//                 {
//                     std::cout << "Received data: ";
//                     std::cout.write(data_.data(), length);
//                     std::cout << std::endl;
//                 }
//             });
//     }

//     tcp::acceptor acceptor_;
//     std::vector<char> data_;
// };

// class UdpServer
// {
// public:
//     UdpServer(asio::io_context& io_context, short port)
//         : socket_(io_context, udp::endpoint(udp::v4(), port))
//     {
//         do_receive();
//     }

// private:
//     void do_receive()
//     {
//         socket_.async_receive_from(
//             asio::dynamic_buffer(data_), sender_endpoint_,
//             [this](std::error_code ec, size_t length)
//             {
//                 if (!ec)
//                 {
//                     std::cout << "Received data from " << sender_endpoint_ << ": ";
//                     std::cout.write(data_.data(), length);
//                     std::cout << std::endl;
//                 }

//                 do_receive();
//             });
//     }

//     udp::socket socket_;
//     udp::endpoint sender_endpoint_;
//     std::vector<char> data_;
// };


#endif /* !SERVER_HPP_ */
