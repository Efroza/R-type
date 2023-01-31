/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/

// #include "iostream"

// int main()
// {
//     std::cout << "Hello World server" << std::endl;
//     return 0;
// }

#include "../include/server.hpp"

int main()
{
    try
    {
        asio::io_context io_context;

        // Start the TCP server on port 12345
        TcpServer tcp_server(io_context, 12345);

        // Start the UDP server on port 12345
        UdpServer udp_server(io_context, 12345);

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}