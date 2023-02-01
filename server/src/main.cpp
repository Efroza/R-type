/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/

#include <iostream>
#include <asio.hpp>
#include <thread>

using namespace asio;

const int BUFSIZE = 1024;
const std::string HOST = "127.0.0.1";
const int PORT = 12345;

char buf[BUFSIZE];

void receive_thread(ip::udp::socket& socket, ip::udp::endpoint& remote) {
    while (true) {
        size_t len = socket.receive_from(buffer(buf, BUFSIZE), remote);
        std::cout << "Received data from " << remote.address().to_string() << ":" << remote.port() << ": ";
        std::cout.write(buf, len) << std::endl;
    }
}

void send_thread(ip::udp::socket& socket, ip::udp::endpoint& remote) {
    while (true) {
        std::cout << "Enter message to send: ";
        std::string message;
        std::getline(std::cin, message);
        socket.send_to(buffer(message), remote);
    }
}

int main() {
    io_service io_service;
    ip::udp::socket socket(io_service, ip::udp::endpoint(ip::udp::v4(), PORT));
    ip::udp::endpoint remote(ip::address::from_string(HOST), PORT);

    std::thread receive(receive_thread, std::ref(socket), std::ref(remote));
    std::thread send(send_thread, std::ref(socket), std::ref(remote));

    receive.join();
    send.join();

    return 0;
}