/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/


#include <iostream>
#include "./include/client.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
    std::string tcp_port = "12346";

    // Lancer la window ici avec un get input pour le port
    if (ac != 2)
    {
        std::cerr << "Usage: ./r-type_client.exe <host>" << std::endl;
        return 84;
    }
    std::string host = av[1];
    // Uncomment the line for the desired client
    Client client(host, tcp_port);
    try {
        Core core(client);
        core.loop();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}