/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Server
*/

#include "../include/Server.hpp"

Server::Server()
{
}

Server::~Server()
{
}

void Server::add_client(uint16_t id, std::shared_ptr<asio::ip::tcp::socket> socket) {
    client_info_map.insert(std::make_pair(id, new ClientInfo(id, socket)));
}

ClientInfo* Server::get_client_info(uint16_t client_id) const {
    auto iter = client_info_map.find(client_id);
    if (iter != client_info_map.end()) {
        return iter->second;
    } else {
        // Handle the case when the client ID is not found
        return NULL;
    }
}

void Server::remove_client(uint16_t client_id) {
    client_info_map.erase(client_id);
}

uint16_t Server::get_nb_clients() const {
    return client_info_map.size();
}
    
void Server::print_all_clients() const {
    for (const auto& iter : client_info_map) {
        iter.second->print_info_clients();
    }
}

void Server::new_client(uint16_t client_id) {
    Header_server header;
    header.data_type = NEW_CLIENT;
    header.id = client_id;
    for (const auto& iter : client_info_map) {
        if (iter.first != client_id) {
            asio::write(*(iter.second->get_socket()), asio::buffer(&header, sizeof(Header_server)));
        }
    }
}