/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/

#include <iostream>
#include <asio.hpp>
#include <thread>
#include <vector>

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

void send_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints) { // Send data to clients
    
    while (true) { // Loop forever thread will send data to clients
        std::cout << "Enter message to send: ";
        std::string message;
        std::getline(std::cin, message);
        for (auto &endpoint : endpoints)
            socket.send_to(buffer(message), endpoint); // Send message to all clients
    }
}

int main() {
    io_service io_service;
    ip::udp::socket socket(io_service, ip::udp::endpoint(ip::udp::v4(), PORT)); // Bind to port
    ip::udp::endpoint remote(ip::address::from_string(HOST), PORT); // Remote endpoint
    std::vector<ip::udp::endpoint> endpoints;

    std::thread receive(receive_thread, std::ref(socket), std::ref(remote), std::ref(endpoints)); // Create thread to receive data from clients
    std::thread send(send_thread, std::ref(socket), std::ref(remote), std::ref(endpoints)); // Create thread to send data to clients


    receive.join(); // Wait for threads 'receive' to finish
    send.join(); // Wait for threads 'send' to finish

    return 0;
}

// void receive_thread(ip::tcp::socket& socket) { // Receive data from clients
//     while (true) { // Loop forever thread will receive data from clients
//         size_t len = socket.read_some(buffer(buf, BUFSIZE));
//         std::cout << "Received data from client: ";
//         std::cout.write(buf, len) << std::endl;
//     }
// }

// void send_thread(ip::tcp::socket& socket) { // Send data to clients
//     while (true) { // Loop forever thread will send data to clients
//         std::cout << "Enter message to send: ";
//         std::string message;
//         std::getline(std::cin, message);
//         socket.write_some(buffer(message));
//     }
// }

// int main() {
//     io_service io_service;
//     ip::tcp::endpoint endpoint(ip::tcp::v4(), PORT);
//     ip::tcp::acceptor acceptor(io_service, endpoint);
//     ip::tcp::socket socket(io_service);

//     std::cout << "Waiting for client connection..." << std::endl;
//     acceptor.accept(socket);
//     std::cout << "Client connected." << std::endl;

//     std::thread receive(receive_thread, std::ref(socket)); // Create thread to receive data from clients
//     std::thread send(send_thread, std::ref(socket)); // Create thread to send data to clients

//     receive.join(); // Wait for threads 'receive' to finish
//     send.join(); // Wait for threads 'send' to finish

//     return 0;
// }