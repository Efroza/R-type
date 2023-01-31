/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/

// #include "iostream"
// #include "stdio.h"

// int main()
// {
//     std::cout << "Hello World client" << std::endl;
//     return 0;
// }

#include "../include/client.hpp"

int main()
{
    try
    {
        asio::io_context io_context;

        // Connect to the server at localhost:12345
        TcpClient tcp_client(io_context, "localhost", "12345");
        tcp_client.send("Hello from TCP client!");

        // Connect to the server at localhost:12345
        UdpClient udp_client(io_context, "localhost", "12345");
        udp_client.send("Hello from UDP client!");

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}