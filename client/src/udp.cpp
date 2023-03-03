/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** udp
*/

#include "../include/client.hpp"

/**
 * @file udp.cpp
 */

/**
 * @details This function will send data to the server.
 * @param socket represents the socket of the client.
 * @param server_endpoint represents the endpoint of the server.
 * @param input represents the input of the user.
 * @return void
 * @details This function will send a certain stuct to the server depending of the message.
 * @details It will create a header with a data type depending of the message.
 * @details If the message contains a comma, it will send a position. If not, it will send a message.
 * @details It will send the header and the struct to the server.
*/
void Client::send_struct_client_udp(udp::socket& socket, udp::endpoint& server_endpoint, std::string input)
{
    Messages message_to_send;
    Position position_to_send;
    Header header_to_send;

    header_to_send.id = 0;
    if (input.find(',') != std::string::npos) { //  If the input contains a comma, it's a position
        header_to_send.data_type = POSITION;
        position_to_send.x = std::stoi(input.substr(0, input.find(',')));
        position_to_send.y = std::stoi(input.substr(input.find(',') + 1, input.size()));
        socket.send_to(asio::buffer(&header_to_send, sizeof(header_to_send)), server_endpoint);
        socket.send_to(asio::buffer(&position_to_send, sizeof(position_to_send)), server_endpoint);
    } else { // If the input doesn't contain a comma, it's a message
        header_to_send.data_type = MESSAGE;
        message_to_send.size = input.size();
        std::memcpy(&message_to_send.message, input.c_str(), input.size());
        socket.send_to(asio::buffer(&header_to_send, sizeof(header_to_send)), server_endpoint);
        socket.send_to(asio::buffer(&message_to_send, sizeof(message_to_send)), server_endpoint);
    }
}

/**
 * @brief Loop to send data to the server.
 * @param socket represents the socket of the client.
 * @param server_endpoint represents the endpoint of the server.
 * @return void
 * @see send_struct_client_udp(udp::socket& socket, udp::endpoint& server_endpoint, std::string input)
 * @details This function will loop to send data to the server.
 * @details It will call send_struct_client_udp to send data to the server.
 * @details It will send data to the server until the server is closed.
*/
void Client::send_data_client_udp(udp::socket& socket, udp::endpoint& server_endpoint)
{
    while (true) // Infinite loop to send data to server
    {
        std::cout << "Enter message to send: ";
        std::string input;
        std::getline(std::cin, input); // Get the input from the user, will be removed later
        send_struct_client_udp(socket, server_endpoint, input);
    }
}

/**
 * @brief This function will translate the data received from the server into a struct.
 * @param header represents the header of the data received.
 * @param socket represents the socket of the client.
 * @param sender_endpoint represents the endpoint of the server.
 * @param ec represents the error code.
 * @return void
 * @details This function will read the data received from the server.
 * @details It creates two struct one if it is a position and another one if it is a message.
 * @details Depending of the data type it will print the data.
 * 
*/
void Client::receive_data_client_udp(Header header, udp::socket& socket, udp::endpoint& sender_endpoint, asio::error_code& ec)
{
    Messages response;
    Position position;

    if (header.data_type == MESSAGE) { // If the data received is a message
        socket.receive_from(asio::buffer(&response, sizeof(Messages)), sender_endpoint, 0, ec);
        std::cout << "MESSAGE" << std::endl;
        std::cout << "Received from server: " << response.size << " ";
        std::cout.write(response.message, response.size) << std::endl;
    } else { // If the data received is a position
        socket.receive_from(asio::buffer(&position, sizeof(Position)), sender_endpoint, 0, ec);
        std::cout << "POSITION" << std::endl;
        std::cout << "Received from server: " << position.x << " " << position.y << std::endl;
    }
}

/**
 * @brief Loop to receive data from the server.
 * @param socket represents the socket of the client.
 * @param io_context represents the io_context of the client.
 * @return void
 * @see receive_data_client_udp(Header header, udp::socket& socket, udp::endpoint& sender_endpoint, asio::error_code& ec)
 * @details This function will loop to receive data from the server.
 * @details It will call receive_data_client_udp to receive data from the server.
 * @details It will receive data from the server until the server is closed.
*/
void Client::receive_thread_client_udp(udp::socket& socket, asio::io_context& io_context)
{
    while (true) { // Infinite loop to receive data from server
        Header header;
        udp::endpoint sender_endpoint;
        asio::error_code ec;
        size_t bytes_received = socket.receive_from(asio::buffer(&header, sizeof(Header)), sender_endpoint, 0, ec);
        
        if (!ec)
            receive_data_client_udp(header, socket, sender_endpoint, ec);
    }
}

/**
 * @brief Launch a UDP client.
 * @param host represents the host of the server.
 * @param port represents the port of the server.
 * @return void
 * @see receive_thread_client_udp(udp::socket& socket, asio::io_context& io_context)
 * @see send_data_client_udp(udp::socket& socket, udp::endpoint& server_endpoint)
 * @details This function will launch a UDP client.
 * @details It will create a thread to receive data from the server and a there is a call to send_data_client_udp to send data to the server.
*/
void Client::async_udp_client(const std::string& host, const std::string& port)
{
    asio::io_context io_context;

    udp::resolver resolver(io_context);
    udp::endpoint server_endpoint = *resolver.resolve(udp::v4(), host, port).begin();

    udp::socket socket(io_context);
    socket.open(udp::v4());

    Header connect_server;
    connect_server.id = 0;
    connect_server.data_type = MESSAGE;
    socket.send_to(asio::buffer(&connect_server, sizeof(connect_server)), server_endpoint); // Connect to server
    std::cout << "Connected to server UDP" << std::endl; // TODO: remove

    std::thread receive_thread(&Client::receive_thread_client_udp, this, std::ref(socket), std::ref(io_context)); // Receive from server thread
    send_data_client_udp(socket, server_endpoint); // Send to server
    receive_thread.join();
}