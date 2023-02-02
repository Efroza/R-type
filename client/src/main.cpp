/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/

#include <iostream>
#include <asio.hpp>

using asio::ip::tcp;
using asio::ip::udp;

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
                    else
                    {
                        // Could not receive response from server
                        std::cout << "No response from server." << std::endl;
                    }
                }
            }
            else
            {
                std::cerr << "Error connecting to the server: " << ec.message() << std::endl;
            }
        });

    io_context.run();
}

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

int main()
{
    std::string host = "localhost";
    std::string port = "12345";

    // Uncomment the line for the desired client
    async_tcp_client(host, port);
    // async_udp_client(host, port);

    return 0;
}