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
#include <fstream>

class Server {
    public:
        Server();
        ~Server();


        // Handle list of clients
        void add_client(uint16_t id, std::shared_ptr<asio::ip::tcp::socket> socket, uint16_t x, uint16_t y);
        ClientInfo* get_client_info(uint16_t client_id) const;
        void remove_client(uint16_t client_id);
        uint16_t get_nb_clients() const;
        void print_all_clients() const;
        void new_client(uint16_t client_id);
        void send_to_all_clients(Server_data data, uint16_t id);

        void send_vector_clients();
    private:
        std::map<uint16_t, ClientInfo*> client_info_map;
};

class TCP_Server {
    public:
        TCP_Server(uint16_t port);
        ~TCP_Server();

        void launch_tcp_server();
        void handle_client(std::shared_ptr<asio::ip::tcp::socket> socket, Server& server_data);
        void send_tcp_server(Header_server header, asio::ip::tcp::socket &socket, std::string message);
        void receive_tcp_server(Header_client header, asio::ip::tcp::socket &socket, Server &server_data);

        void new_client_create_lobby(std::shared_ptr<asio::ip::tcp::socket> socket, Server& server_data, uint16_t client_id);

    private:
        Server server_data;
        std::thread start;
        bool _lobby = false;
        uint16_t _port;
        uint16_t _nb_clients = 0;
        uint16_t _nb_lobby = 0;
        uint16_t last_x = 50;
};

class UDP_Server {
    public:
        UDP_Server();
        ~UDP_Server();

        void launch_udp_server();
        void send_thread(asio::ip::udp::socket& socket, asio::ip::udp::endpoint& remote, std::vector<asio::ip::udp::endpoint>& endpoints);
        void send_message(asio::ip::udp::socket& socket, std::vector<asio::ip::udp::endpoint>& endpoints, std::string message_client);
        void send_position(asio::ip::udp::socket& socket, std::vector<asio::ip::udp::endpoint>& endpoints, std::string message_client);
        void receive_thread(asio::ip::udp::socket& socket, asio::ip::udp::endpoint& remote, std::vector<asio::ip::udp::endpoint>& endpoints);
        void receive_data(asio::ip::udp::socket& socket, asio::ip::udp::endpoint& remote, std::vector<asio::ip::udp::endpoint>& endpoint, Header header);

    private:
        std::thread start;
};

#endif /* !SERVER_HPP_ */
