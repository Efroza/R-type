/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#ifdef _WIN32
#include "../../framework.h"
#endif

#include "../../shared/include/headers.hpp"
#include "../../shared/include/ClientInfo.hpp"

void launch_tcp_server();
void launch_udp_server();

class Server {
    public:
        Server() {}
        ~Server() {}

        void add_client(uint16_t id, std::shared_ptr<asio::ip::tcp::socket> socket) {
            client_info_map.insert(std::make_pair(id, new ClientInfo(id, socket)));
            // client_info_map[client_id] = ClientInfo(client_id);
        }

        ClientInfo* get_client_info(uint16_t client_id) const {
            auto iter = client_info_map.find(client_id);
            if (iter != client_info_map.end()) {
                return iter->second;
            } else {
                // Handle the case when the client ID is not found
                return NULL;
            }
        }

        void remove_client(uint16_t client_id) {
            client_info_map.erase(client_id);
        }

        uint16_t get_nb_clients() const {
            return client_info_map.size();
        }
    
        void print_all_clients() const {
            for (const auto& iter : client_info_map) {
                iter.second->print_info_clients();
            }
        }

private:
    std::map<uint16_t, ClientInfo*> client_info_map;
};

#endif /* !SERVER_HPP_ */
