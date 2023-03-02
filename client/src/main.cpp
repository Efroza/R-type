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
    // Lancer la window ici avec un get input pour le port
    if (ac != 3) {
        std::cerr << "Usage: ./r-type_client.exe <host> <port>" << std::endl;
        return 84;
    }
    std::string host = av[1];
    std::string tcp_port = av[2];
    Client client(host, tcp_port);

    return 0;
}