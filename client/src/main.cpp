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
    std::string tcp_port = "12346";

    // Uncomment the line for the desired client
    async_udp_client(host, port);
    // async_tcp_client(host, tcp_port);

    return 0;
}