/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "iostream"

class network
{
    public:
        network(const std::string &ip_address, size_t port);
        ~network();
        void connexion_network(); //socket de connexion à un réseaux throw si erreur
    private:
        std::string ip_adress;
        size_t port;
};

#endif /* !NETWORK_HPP_ */