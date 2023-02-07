/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/

#include "../include/server.hpp"

int main() {
    // Uncomment the line for the desired server
    // std::thread first(launch_tcp_server);
    std::thread second(launch_udp_server);

    // first.join();
    second.join();

    return 0;
}