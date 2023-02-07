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

// const int BUF_LENGTH = 1024;
// char buffer_message[BUF_LENGTH];

void handle_client(tcp::socket socket)
{
  std::cout << "Accepted connection from " << socket.remote_endpoint().address() << std::endl;
  while (true) {
    Header header;
    // size_t len = socket.read_some(asio::buffer(buffer_message, BUF_LENGTH));
    size_t len = socket.read_some(asio::buffer(&header, sizeof(Header)));
    if (header.data_type == POSITION) {
        Position position;
        socket.read_some(asio::buffer(&position, sizeof(Position)));
        std::cout << "Received from client " << header.id << ": " << position.x << " " << position.y << std::endl;
    } else {
        Messages message;
        socket.read_some(asio::buffer(&message, sizeof(Messages)));
        std::cout << "Received from client " << header.id << ": " << message.size << " ";
        std::cout.write(message.message, message.size) << std::endl;
    }
    std::cout << "Enter message to send: ";
    std::string message;
    std::getline(std::cin, message);
    std::memset(&header, 0, sizeof(header));
    header.id = 1;
    if (std::find(message.begin(), message.end(), ',') != message.end()) { //  If the input contains a comma, it's a position
        header.data_type = POSITION;
        Position position_to_send;
        position_to_send.x = std::stoi(message.substr(0, message.find(',')));
        position_to_send.y = std::stoi(message.substr(message.find(',') + 1, message.size()));
        socket.send(asio::buffer(&header, sizeof(header)));
        socket.send(asio::buffer(&position_to_send, sizeof(position_to_send)));
    } else { // If the input doesn't contain a comma, it's a message
        header.data_type = MESSAGE;
        Messages message_to_send;
        message_to_send.size = message.size();
        std::memcpy(&message_to_send.message, message.c_str(), message.size());
        socket.send(asio::buffer(&header, sizeof(header)));
        socket.send(asio::buffer(&message_to_send, sizeof(message_to_send)));
    }
    // socket.write_some(asio::buffer(message, message.size()));
  }
}

void launch_tcp_server()
{
  io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12346));
  while (true) {
    tcp::socket socket(io_context);
    acceptor.accept(socket);
    std::thread t(handle_client, std::move(socket));
    t.detach();
  }
}