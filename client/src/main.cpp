/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/

#include "../include/client.hpp"

int main()
{
    std::string host = "localhost";
    std::string port = "12345";

    // Uncomment the line for the desired client
    // async_tcp_client(host, port);
    async_udp_client(host, port);

    return 0;
}