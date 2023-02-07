/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/

#include "../include/server.hpp"

/**
 * @file main.cpp
 * @brief Launch a TCP server and UDP server
 * @return int
 * @details Launch a TCP server and UDP server both of them are called in threads. They are both in threads so we can use them at the same time and they are joined at the end of the main so the program doesn't end before the threads
 */

int main() {
    // Uncomment the line for the desired server
    std::thread first(launch_tcp_server);
    // std::thread second(launch_udp_server);

    first.join();
    // second.join();

    return 0;
}