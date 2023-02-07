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

void receive_data(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoint, Header header) {
    Position position;
    Messages message;
    if (header.data_type == POSITION) { // If data type is position (two int32)
        std::cout << "POSITION" << std::endl;
        socket.receive_from(asio::buffer(&position, sizeof(Position)), remote);
        std::cout << "Received from client " << header.id << ": " << position.x << " " << position.y << std::endl;
    } else { // If data type is message (string32 + int32)
        std::cout << "MESSAGE" << std::endl;
        socket.receive_from(asio::buffer(&message, sizeof(Messages)), remote);
        std::cout << "Received from client " << header.id << ": " << message.size << " ";
        std::cout.write(message.message, message.size) << std::endl;
    }
}

void receive_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints) { // Receive data from clients
    while (true) { // Loop forever thread will receive data from clients
        Header header;

        size_t len = socket.receive_from(buffer(&header, sizeof(Header)), remote); // Receive header
        if (std::find(endpoints.begin(), endpoints.end(), remote) == endpoints.end()) {
            endpoints.push_back(remote);
            // header.id = endpoints.size();
            std::cout << "New client connected: " << remote.address().to_string() << ":" << remote.port() << ". Id = " << endpoints.size() << "." << std::endl;
            continue;
        } else {
            header.id = std::find(endpoints.begin(), endpoints.end(), remote) - endpoints.begin() + 1; // Because for now the id sent by the client isn't the id of the client
        }
        receive_data(socket, remote, endpoints, header);
    }
}

void send_position(ip::udp::socket& socket, std::vector<ip::udp::endpoint>& endpoints, std::string message_client) { // Send struct position to clients
    Header header;
    Position position_to_send;
    header.data_type = POSITION; // Set data type to position
    position_to_send.x = std::stoi(message_client.substr(0, message_client.find(',')));
    position_to_send.y = std::stoi(message_client.substr(message_client.find(',') + 1, message_client.size()));
    for (auto &endpoint : endpoints) { // Send data to all clients
        header.id = std::find(endpoints.begin(), endpoints.end(), endpoint) - endpoints.begin() + 1;
        socket.send_to(asio::buffer(&header, sizeof(header)), endpoint); // Send header
        socket.send_to(asio::buffer(&position_to_send, sizeof(position_to_send)), endpoint); // Send position
    }
}

void send_message(ip::udp::socket& socket, std::vector<ip::udp::endpoint>& endpoints, std::string message_client) { // Send struct message to clients
    Header header;
    Messages message_to_send;
    header.data_type = MESSAGE; // Set data type to message
    message_to_send.size = message_client.size();
    std::memcpy(&message_to_send.message, message_client.c_str(), message_client.size());
    for (auto &endpoint : endpoints) { // Send data to all clients
        header.id = std::find(endpoints.begin(), endpoints.end(), endpoint) - endpoints.begin() + 1; // Will be change later to only get id from the client we want
        socket.send_to(asio::buffer(&header, sizeof(header)), endpoint);
        socket.send_to(asio::buffer(&message_to_send, sizeof(message_to_send)), endpoint);
    }
}

void send_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints) { // Send data to clients
    
    while (true) { // Loop forever thread will send data to clients
        std::cout << "Enter message to send: ";
        std::string message_client;
        std::getline(std::cin, message_client); // Get message from user, will be removed later when automatic data is sent
        if (message_client.find(',') != std::string::npos)
            send_position(socket, endpoints, message_client); // Send struct position to client
        else
            send_message(socket, endpoints, message_client); // Send struct message to client
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