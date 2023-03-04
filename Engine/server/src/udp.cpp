/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** udp
*/

#include "../include/server.hpp"

using namespace asio;

const int BUFSIZE = 1024;
const std::string HOST = "127.0.0.1"; // Localhost : 127.0.0.1

/**
 *@file udp.cpp
 */

UDP_Server::UDP_Server(uint16_t port)
: _port(port)
, io_service()
, socket(io_service, ip::udp::endpoint(ip::udp::v4(), _port))
, remote(ip::address::from_string(HOST), _port)
, reg(nullptr)
{
    start = std::thread(&UDP_Server::launch_udp_server, this);
}

UDP_Server::~UDP_Server()
{
    start.join();
}

/**
 * @brief This function will retrieve the current port of the udp server
 * @return uint16_t
*/
uint16_t UDP_Server::get_port() const
{
    return _port;
}

void UDP_Server::launch_thread_server() 
{
    start = std::thread(&UDP_Server::launch_udp_server, this);
    start.detach();
}
/**
 * @brief This function will launch the udp server.
 * @return void
 * @param void
 * @see receive_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints)
 * @see send_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints)
 * @details This function will launch the udp server, it will create two threads, one to receive data from clients and one to send data to clients. After the threads are created it will wait for them to finish with join().
*/
void UDP_Server::launch_udp_server()
{
    // io_service io_service;
    // ip::udp::socket socket(io_service, ip::udp::endpoint(ip::udp::v4(), _port)); // Bind to por
    std::cout << "UDP Server started on port " << _port << std::endl;
    // ip::udp::endpoint remote(ip::address::from_string(HOST), _port); // Remote endpoint
    // std::vector<ip::udp::endpoint> endpoints;

    std::thread receive(&UDP_Server::receive_thread, this, std::ref(socket), std::ref(remote), std::ref(endpoints)); // Create thread to receive data from clients
    std::thread send(&UDP_Server::send_thread, this, std::ref(socket), std::ref(remote), std::ref(endpoints)); // Create thread to send data to clients

    receive.join(); // Wait for threads 'receive' to finish
    send.join(); // Wait for threads 'send' to finish
}

/**
 * @brief This function will send data to the clients.
 * @return void
 * @param socket the socket of the server to send data to client
 * @param remote the remote endpoint of the client
 * @param endpoints the vector of all the endpoints of the clients
 * @see send_position(ip::udp::socket& socket, std::vector<ip::udp::endpoint>& endpoints, std::string message_client)
 * @see send_message(ip::udp::socket& socket, std::vector<ip::udp::endpoint>& endpoints, std::string message_client)
 * @details This function will send data to the clients. It will send a struct position or a struct message to the clients depending if in the message there is a comma or no.
 * @details If there is a comma, it will send a struct position, if not it will send a struct message.
*/
void UDP_Server::send_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints)  // Send data to clients
{
    while (true) { // Loop forever thread will send data to clients
        std::cout << "Enter message to send: ";
        std::string message_client;
        std::getline(std::cin, message_client); // Get message from user, will be removed later when automatic data is sent
        if (message_client.find(',') != std::string::npos)
            send_position(socket, endpoints, message_client); // Send struct position to client
        else
            send_message(socket, endpoints, message_client); // Send  struct message to client
    }
}

/**
 * @brief this function will send the struct message to the clients.
 * @return void
 * @param socket the socket of the server to send data to client
 * @param endpoints the vector of all the endpoints of the clients
 * @param message_client the message to send to the clients
 * @details This function will send a certain message to the clients.
 * @details It will first send the struct message to the clients, then the struct header to know that it is a message.
*/
void UDP_Server::send_message(ip::udp::socket& socket, std::vector<ip::udp::endpoint>& endpoints, std::string message_client) // Send struct message to clients
{
    Header header;
    Messages message_to_send;
    header.data_type = MESSAGE; // Set data type to message
    message_to_send.size = message_client.size();
    std::memcpy(&message_to_send.message, message_client.c_str(), message_client.size());
    for (auto &endpoint : endpoints) { // Send data to all clients
        header.id = std::find(endpoints.begin(), endpoints.end(), endpoint) - endpoints.begin() + 1; // Will be change later to only get id from the client we want
        socket.send_to(asio::buffer(&header, sizeof(header)), endpoint);
        socket.send_to(asio::buffer(&message_to_send, sizeof(message_to_send)), endpoint);
    }
}

/**
 * @brief This function will send the struct position to the clients.
 * @return void
 * @param socket the socket of the server to send data to client
 * @param endpoints the vector of all the endpoints of the clients
 * @param message_client the message to send to the clients
 * @details This function will send a certain position to the clients.
 * @details It will first send the struct position to the clients, then the struct header to know that it is a position.
*/
void UDP_Server::send_position(ip::udp::socket& socket, std::vector<ip::udp::endpoint>& endpoints, std::string message_client) // Send struct position to clients
{
    Header header;
    Position position_to_send;
    header.data_type = POSITION; // Set data type to position
    position_to_send.x = std::stoi(message_client.substr(0, message_client.find(',')));
    position_to_send.y = std::stoi(message_client.substr(message_client.find(',') + 1, message_client.size()));
    for (auto &endpoint : endpoints) { // Send data to all clients
        header.id = std::find(endpoints.begin(), endpoints.end(), endpoint) - endpoints.begin() + 1;
        socket.send_to(asio::buffer(&header, sizeof(header)), endpoint); // Send header
        socket.send_to(asio::buffer(&position_to_send, sizeof(position_to_send)), endpoint); // Send position
    }
}

/**
 * @brief This function will send the struct position to the clients.
 * @return void
 * @param position_to_send structure who contain a x and y
 * @details This function will send a certain position to the clients.
 * @details It will first send the struct position to the clients, then the struct header to know that it is a position.
 */

void UDP_Server::send_position(std::uint16_t client_id, Position position_to_send) // Send struct position to clients
{
    Header header;
    header.data_type = POSITION; // Set data type to position
    header.id = client_id;
    for (auto &endpoint : endpoints)
    { // Send data to all clients
        // header.id = std::find(endpoints.begin(), endpoints.end(), endpoint) - endpoints.begin() + 1;
        socket.send_to(asio::buffer(&header, sizeof(header)), endpoint);                     // Send header
        socket.send_to(asio::buffer(&position_to_send, sizeof(position_to_send)), endpoint); // Send position
    }
}

/**
 * @brief This function will receive data from the clients.
 * @return void
 * @param socket the socket of the server to send data to client
 * @param remote the remote endpoint of the client
 * @param endpoints the vector of all the endpoints of the clients
 * @see void receive_data(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoint, Header header)
 * @details This function will receive data from the clients and will call receive_data to get the data.
 * @details It will also check if the client is already connected and if not it will add it to the vector of endpoints.
*/
void UDP_Server::receive_thread(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoints) // Receive data from clients
{
    std::cout << "Waiting for clients to connect..." << std::endl;
    while (true) { // Loop forever thread will receive data from clients
        Header header;

        size_t len = socket.receive_from(buffer(&header, sizeof(Header)), remote); // Receive header
        if (std::find(endpoints.begin(), endpoints.end(), remote) == endpoints.end()) {
            endpoints.push_back(remote);
            // header.id = endpoints.size();
            std::cout << "New client connected: " << remote.address().to_string() << ":" << remote.port() << ". Id = " << endpoints.size() << "." << std::endl;
            for (auto &new_client : new_client_function)
                new_client(endpoints.size(), reg, *this);
            continue;
        } else {
            header.id = std::find(endpoints.begin(), endpoints.end(), remote) - endpoints.begin() + 1; // Because for now the id sent by the client isn't the id of the client
        }
        receive_data(socket, remote, endpoints, header);
    }
}

/**
 *@brief This function will translate the message received from a client.
 *@return void
 *@param socket the socket of the server to send data to client
 *@param remote the remote endpoint of the client
 *@param endpoints the vector of all the endpoints of the clients
 *@param header the header of the data to know the type of data
 *@details This function will read the message that was sent from the client and will print it.
 *@details It creates two struct one if it is a position and another one if it is a message.
 *@details Depending of the data type it will print the data.
*/
void UDP_Server::receive_data(ip::udp::socket& socket, ip::udp::endpoint& remote, std::vector<ip::udp::endpoint>& endpoint, Header header)
{
    Position position;
    Messages message;
    if (header.data_type == POSITION) { // If data type is position (two int32)
        std::cout << "POSITION" << std::endl;
        socket.receive_from(asio::buffer(&position, sizeof(Position)), remote);
        std::cout << "Received from client " << header.id << ": " << position.x << " " << position.y << std::endl;
    } else { // If data type is message (string32 + int32)
        std::cout << "MESSAGE" << std::endl;
        socket.receive_from(asio::buffer(&message, sizeof(Messages)), remote);
        std::cout << "Received from client " << header.id << ": " << message.size << " ";
        std::cout.write(message.message, message.size) << std::endl;
    }
}

/**
 *@brief This function will add a function
 *@return void
 *@param new_function function who will declanche with a new connection udp
 *@details This function will add a function who will declanche it with a new udp connection
 */

void UDP_Server::add_new_client_function(std::function<void(std::uint16_t, registry *, UDP_Server &)> new_function) noexcept
{
    new_client_function.emplace_back(std::move(new_function));
}

/**
 *@brief This function will set the registry of the game design
 *@return void
 *@param my_reg registry of the game server
 *@details This function will set the pointer registry of the UDP class
 */

void UDP_Server::set_registry(registry &my_reg) noexcept
{
    reg = &my_reg;
}