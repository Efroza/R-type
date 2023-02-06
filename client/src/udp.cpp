/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** udp
*/

#include "../include/client.hpp"

struct message {
    int32_t id;
    int32_t len;
    char data[1024];
};

void async_udp_client(const std::string& host, const std::string& port)
{
    asio::io_context io_context;

    udp::resolver resolver(io_context);
    // asio::ip::udp::endpoint server_endpoint = *resolver.resolve(udp::v4(), host, port).begin();
    udp::endpoint server_endpoint = *resolver.resolve(udp::v4(), host, port).begin();

    udp::socket socket(io_context);
    socket.open(udp::v4());

    message msg;
    msg.id = 0;
    msg.len = 12;
    std::memcpy(&msg.data, "Connected", 12);

    socket.send_to(asio::buffer(&msg, sizeof(msg)), server_endpoint);
    std::cout << "Connected to server" << std::endl;

    std::thread receive_thread([&socket, &io_context](){
        while (true)
    {
        message response;
        udp::endpoint sender_endpoint;
        asio::error_code ec;
        size_t bytes_received = socket.receive_from(asio::buffer(&response, sizeof(message)), sender_endpoint, 0, ec);

        if (!ec)
        {
            // Received response from server
            std::cout << "Received from server: " << response.id << " " << response.len << " ";
            std::cout.write(response.data, response.len) << std::endl;
        }
    }
    });

    while (true)
    {
        std::cout << "Enter message to send: ";
        std::string input;
        std::getline(std::cin, input);
        msg.id = 1;
        msg.len = input.length();
        // std::strcpy(&msg.data, input.c_str());
        std::memcpy(&msg.data, input.c_str(), input.length());

        // Send the message to the server
        socket.send_to(asio::buffer(&msg, sizeof(message)), server_endpoint);
    }

    receive_thread.join();
}