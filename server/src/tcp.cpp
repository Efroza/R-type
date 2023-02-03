/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** tcp
*/

#include "../include/server.hpp"

using asio::io_context;
using asio::ip::tcp;
using asio::buffer;

const int BUF_LENGTH = 1024;
char buffer_message[BUF_LENGTH];

void handle_client(tcp::socket socket)
{
  std::cout << "Accepted connection from " << socket.remote_endpoint().address() << std::endl;
  while (true) {
    size_t len = socket.read_some(asio::buffer(buffer_message, BUF_LENGTH));
    std::cout << "Received message: ";
    std::cout.write(buffer_message, len) << std::endl;
    std::cout << "Enter message to send: ";
    std::string message;
    std::getline(std::cin, message);
    socket.write_some(asio::buffer(message, message.size()));
  }
}

void launch_tcp_server()
{
  io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));
  while (true) {
    tcp::socket socket(io_context);
    acceptor.accept(socket);
    std::thread t(handle_client, std::move(socket));
    t.detach();
  }
}