/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** main
*/


#include <iostream>
#include "Core.hpp"

int main(int ac, char **av)
{
    try {
        Core core;
        core.loop();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}