/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** tcp
*/

#include "../include/client.hpp"

void async_tcp_client(const std::string& host, const std::string& port)
{
    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, port);

    tcp::socket socket(io_context);
    asio::async_connect(socket, endpoints,
        [&](const asio::error_code& ec, tcp::endpoint)
        {
            if (!ec)
            {
                // Connected to the server successfully
                std::cout << "Connected to the server via TCP." << std::endl;

                while (true)
                {
                    std::cout << "Enter message to send: ";
                    std::string message;
                    std::getline(std::cin, message);

                    // Send the message to the server
                    asio::write(socket, asio::buffer(message));

                    // Try to receive the response from the server
                    char response[1024];
                    size_t bytes_received = socket.read_some(asio::buffer(response, 1024));

                    if (!ec)
                    {
                        // Received response from server
                        std::cout << "Received from server: ";
                        std::cout.write(response, bytes_received) << std::endl;
                    }
                }
            }
        });

    io_context.run();
}