/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/

#include "../include/client.hpp"

/**
 * @file main.cpp
 */

/**
 * @brief Launch a TCP client and UDP client.
 * @return int
 * @details Launch a TCP client and UDP client uncomment desired client.
 */

int main(int ac, char **av)
{
    std::string port = "12345";
    std::string tcp_port = "12346";

    if (ac != 2) {
        std::cerr << "Usage: ./r-type_client.exe <host>" << std::endl;
        return 84;
    }
    std::string host = av[1];
    // Uncomment the line for the desired client
    async_tcp_client(host, tcp_port);
    // async_udp_client(host, port);

    return 0;
}