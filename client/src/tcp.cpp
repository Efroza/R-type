/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** tcp
*/

#include "../include/client.hpp"

/**
 * @file tcp.cpp
 */

/**
 * @brief This function will translate the data received from the server.
 * @return void
 * @param header the header of the data to know the type of data
 * @param socket the socket of the client to receive data from server
 * @details This function will read the data that was sent from the server and will print it.
 * @details It creates two struct one if it is a position and another one if it is a message.
 * @details Depending of the data type it will print the data.
*/
void receive_tcp_client(Header_server header, tcp::socket &socket) {
    if (header.data_type == MESSAGESS) {
        Messages message;
        socket.receive(asio::buffer(&message, sizeof(Messages)));
        std::cout << "Received from server " << header.id << ": " << message.size << " ";
        std::cout.write(message.message, message.size) << std::endl;
    } else if (header.data_type == NEW_CLIENT) {
        std::cout << "New client connected with id : " << header.id << std::endl;
    } else {
        std::cout << "Wrong data type" << std::endl;
    }
}

/**
 * @brief This function will send data to the server.
 * @return void
 * @param header the header of the data to know the type of data
 * @param socket the socket of the client to send data to server
 * @param message the message to send to the server
 * @details This function will send data to the server.
 * @details It will create a header with a data type depending of the message.
 * @details It will also create a struct depending of the data type.
 * @details It will send the header and the struct to the server.
 * @details If the message contains a comma it will be a position and if not, it will be a message.
 */
void send_tcp_client(Header_client header, tcp::socket &socket, std::string message) {
    header.data_type = MESSAGES;
    Messages message_to_send;
    message_to_send.size = message.size();
    std::memcpy(&message_to_send.message, message.c_str(), message.size());
    socket.send(asio::buffer(&header, sizeof(header)));
    socket.send(asio::buffer(&message_to_send, sizeof(message_to_send)));
}

/**
 * @brief Launch a TCP client.
 * @param host represents the host of the server
 * @param port represents the port of the server
 * @return void
 * @see send_tcp_client(Header_client header, tcp::socket &socket, std::string message)
 * @see receive_tcp_client(Header_server header, tcp::socket &socket)
 * @details Launch an asynchronous TCP client.
 * @details The client can either send a message or a position.
 * 
 */
void async_tcp_client(const std::string& host, const std::string& port)
{
    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, port);

    tcp::socket socket(io_context);
    asio::async_connect(socket, endpoints,
        [&](const asio::error_code& ec, tcp::endpoint)
        {
            if (!ec)
            {
                // Connected to the server successfully
                std::cout << "Connected to the server via TCP." << std::endl;

                while (true)
                {
                    std::cout << "Enter message to send: ";
                    std::string message;
                    std::getline(std::cin, message);
                    Header_client header_client;
                    header_client.id = 1;

                    // Send the message to the server
                    send_tcp_client(header_client, socket, message);
                    Header_server header_server;
                    std::memset(&header_server, 0, sizeof(header_server));
                    size_t bytes_received = socket.receive(asio::buffer(&header_server, sizeof(header_server)));
                    // If the server has sent a message, receive it
                    if (!ec)
                        receive_tcp_client(header_server, std::ref(socket));
                }
            }
        });

    io_context.run();
}