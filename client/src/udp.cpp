/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** udp
*/

#include "../include/client.hpp"

struct message {
    int32_t id;
    int32_t len;
    char data[1024];
};

void async_udp_client(const std::string& host, const std::string& port)
{
    asio::io_context io_context;

    udp::resolver resolver(io_context);
    // asio::ip::udp::endpoint server_endpoint = *resolver.resolve(udp::v4(), host, port).begin();
    udp::endpoint server_endpoint = *resolver.resolve(udp::v4(), host, port).begin();

    udp::socket socket(io_context);
    socket.open(udp::v4());

    message msg;
    msg.id = 0;
    msg.len = 12;
    std::memcpy(&msg.data, "Connected", 12);

    socket.send_to(asio::buffer(&msg, sizeof(msg)), server_endpoint);
    std::cout << "Connected to server" << std::endl;

    std::thread receive_thread([&socket, &io_context](){
        while (true) {
            Messages response;
            Position position;
            Header header;
            udp::endpoint sender_endpoint;
            asio::error_code ec;
            size_t bytes_received = socket.receive_from(asio::buffer(&header, sizeof(Header)), sender_endpoint, 0, ec);
            
            if (!ec) {
                if (header.data_type == MESSAGE) {
                    socket.receive_from(asio::buffer(&response, sizeof(Messages)), sender_endpoint, 0, ec);
                    std::cout << "MESSAGE" << std::endl;
                    std::cout << "Received from server: " << response.size << " ";
                    std::cout.write(response.message, response.size) << std::endl;
                } else {
                    socket.receive_from(asio::buffer(&position, sizeof(Position)), sender_endpoint, 0, ec);
                    std::cout << "POSITION" << std::endl;
                    std::cout << "Received from server: " << position.x << " " << position.y << std::endl;
                }
            }
        }
    });

    while (true)
    {
        std::cout << "Enter message to send: ";
        std::string input;
        std::getline(std::cin, input);
        Messages message_to_send;
        Position position_to_send;
        Header header_to_send;
        header_to_send.id = 0;
        if (input.find(',') != std::string::npos) {
            header_to_send.data_type = POSITION;
            position_to_send.x = std::stoi(input.substr(0, input.find(',')));
            std::cout << "X: " << position_to_send.x << std::endl;
            position_to_send.y = std::stoi(input.substr(input.find(',') + 1, input.size()));
            std::cout << "Y: " << position_to_send.y << std::endl;
            socket.send_to(asio::buffer(&header_to_send, sizeof(header_to_send)), server_endpoint);
            socket.send_to(asio::buffer(&position_to_send, sizeof(position_to_send)), server_endpoint);
        } else {
            header_to_send.data_type = MESSAGE;
            message_to_send.size = input.size();
            std::memcpy(&message_to_send.message, input.c_str(), input.size());
            socket.send_to(asio::buffer(&header_to_send, sizeof(header_to_send)), server_endpoint);
            socket.send_to(asio::buffer(&message_to_send, sizeof(message_to_send)), server_endpoint);
        }
        // std::strcpy(&msg.data, input.c_str());
        // std::memcpy(&msg.data, input.c_str(), input.length());

        // Send the message to the server
        // socket.send_to(asio::buffer(&msg, sizeof(message)), server_endpoint);
    }

    receive_thread.join();
}