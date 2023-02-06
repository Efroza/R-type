/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** udp
*/

#include "../include/server.hpp"
#include <fstream>

using namespace asio;

const int BUFSIZE = 1024;
const std::string HOST = "127.0.0.1"; // Localhost : 127.0.0.1
const int PORT = 12345; // Port to listen on

char buf[BUFSIZE];

struct message {
    int32_t id;
    int32_t len;
    char data[1024];
};

void receive_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints) { // Receive data from clients
    while (true) { // Loop forever thread will receive data from clients
        message msg;
        std::memset(&msg, 0, sizeof(msg));


        size_t len = socket.receive_from(buffer(&msg, sizeof(msg)), remote);
        if (std::find(endpoints.begin(), endpoints.end(), remote) == endpoints.end()) {
            endpoints.push_back(remote);
            msg.id = endpoints.size();
            std::cout << "New client connected: " << remote.address().to_string() << ":" << remote.port() << ". Id = " << endpoints.size() << "." << std::endl;
        }
        else
            msg.id = std::find(endpoints.begin(), endpoints.end(), remote) - endpoints.begin() + 1;
        std::cout << "Received data from client " << msg.id << ": ";
        std::cout.write(msg.data, msg.len) << std::endl;
    }
}

void send_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints) { // Send data to clients
    
    while (true) { // Loop forever thread will send data to clients
        std::cout << "Enter message to send: ";
        std::string message_client;
        std::getline(std::cin, message_client);
        message msg;
        msg.id = 1;
        msg.len = message_client.size();
        std::memcpy(&msg.data, message_client.c_str(), message_client.size());
        for (auto &endpoint : endpoints)
            socket.send_to(asio::buffer(&msg, sizeof(msg)), endpoint);
    }
}

void launch_udp_server() {
    io_service io_service;
    ip::udp::socket socket(io_service, ip::udp::endpoint(ip::udp::v4(), PORT)); // Bind to port
    ip::udp::endpoint remote(ip::address::from_string(HOST), PORT); // Remote endpoint
    std::vector<ip::udp::endpoint> endpoints;

    std::thread receive(receive_thread, std::ref(socket), std::ref(remote), std::ref(endpoints)); // Create thread to receive data from clients
    std::thread send(send_thread, std::ref(socket), std::ref(remote), std::ref(endpoints)); // Create thread to send data to clients


    receive.join(); // Wait for threads 'receive' to finish
    send.join(); // Wait for threads 'send' to finish
}