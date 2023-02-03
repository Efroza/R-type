/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** udp
*/

#include "../include/server.hpp"

using namespace asio;

const int BUFSIZE = 1024;
const std::string HOST = "127.0.0.1"; // Localhost : 127.0.0.1
const int PORT = 12345; // Port to listen on

char buf[BUFSIZE];

void receive_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints) { // Receive data from clients
    while (true) { // Loop forever thread will receive data from clients
        size_t len = socket.receive_from(buffer(buf, BUFSIZE), remote);


        if (std::find(endpoints.begin(), endpoints.end(), remote) == endpoints.end()) {
            endpoints.push_back(remote);
            std::cout << "New client connected: " << remote.address().to_string() << ":" << remote.port() << ". Id = " << endpoints.size() << "." << std::endl;
        }
        std::cout << "Received data from client " << std::find(endpoints.begin(), endpoints.end(), remote) - endpoints.begin() + 1 << ": ";
        std::cout.write(buf, len) << std::endl;
    }
}

// int32_t lose_hp(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints, std::string message) {
//     if (message.find("Player Hit") != std::string::npos) {
//         // Get what's after : , the string will look like Player Hit : (1),(1)
//         std::string player_hit = message.substr(message.find(":") + 2);
//         // Get the first number
//         std::string player_hit_hp_lost = player_hit.substr(0, player_hit.find(","));
//         // Get the second number
//         std::string player_hit_id = player_hit.substr(player_hit.find(",") + 1);
//         // Convert the string to int
//         int32_t player_hit_hp_lost_int = std::stoi(player_hit_hp_lost);
//         int32_t player_hit_id_int = std::stoi(player_hit_id);
//     }
// }

void send_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints) { // Send data to clients
    
    while (true) { // Loop forever thread will send data to clients
        std::cout << "Enter message to send: ";
        std::string message;
        std::getline(std::cin, message);
        // lose_hp(socket, remote, endpoints, message);
        for (auto &endpoint : endpoints)
            socket.send_to(buffer(message), endpoint); // Send message to all clients
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