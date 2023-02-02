/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** udp
*/

#include "../include/client.hpp"

void async_udp_client(const std::string& host, const std::string& port)
{
    asio::io_context io_context;

    udp::resolver resolver(io_context);
    udp::endpoint server_endpoint = *resolver.resolve(udp::v4(), host, port).begin();

    udp::socket socket(io_context);
    socket.open(udp::v4());
    socket.send_to(asio::buffer("Connected to server"), server_endpoint);
    std::cout << "Connected to server" << std::endl;


    std::thread receive_thread([&socket, &io_context](){
        while (true)
    {
        // Try to receive the response from the server
        char response[1024];
        udp::endpoint sender_endpoint;
        asio::error_code ec;
        size_t bytes_received = socket.receive_from(asio::buffer(response, 1024), sender_endpoint, 0, ec);

        if (!ec)
        {
            // Received response from server
            std::cout << "Received from server: ";
            std::cout.write(response, bytes_received) << std::endl;
        }
    }
    });

    while (true)
    {
        std::cout << "Enter message to send: ";
        std::string message;
        std::getline(std::cin, message);

        // Send the message to the server
        socket.send_to(asio::buffer(message), server_endpoint);
    }

    receive_thread.join();
}