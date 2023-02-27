/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** tcp
*/

#include "../include/Server.hpp"
#include <mutex>

using asio::io_context;
using asio::ip::tcp;
using asio::buffer;

std::mutex mutex;
/**
 * @file tcp.cpp
*/

/**
 * @brief This function will translate the data received from the client.
 * @return void
 * @param header the header of the data to know the type of data
 * @param socket the socket of the server to receive data from client
 * @details This function will read the data that was sent from the client and will print it.
 * @details It creates two struct one if it is a position and another one if it is a message.
 * @details Depending of the data type it will print the data.
*/
void receive_tcp_server(Header_client header, tcp::socket &socket) {
  if (header.data_type == MESSAGES) {
    Messages message;
    socket.receive(asio::buffer(&message, sizeof(Messages)));
    std::cout << "Received from client " << header.id << ": " << message.size << " ";
    std::cout.write(message.message, message.size) << std::endl;
  } else if (header.data_type == LOBBY) {
    std::cout << "Waiting for " << header.id << " players" << std::endl;
  } else {
    std::cout << "Wrong data type" << std::endl;
  }
}

/**
 * @brief This function will send data to the client.
 * @return void
 * @param header the header of the data to know the type of data
 * @param socket the socket of the server to send data to client
 * @param message the message to send to the client
 * @details This function will send data to the client.
 * @details It will create a header with a data type depending of the message.
 * @details It will also create a struct depending of the data type.
 * @details It will send the header and the struct to the client.
 * @details If the message contains a comma it will be a position and if not, it will be a message.
*/
void send_tcp_server(Header_server header, tcp::socket &socket, std::string message) {
  header.id = 1;
  header.data_type = MESSAGESS;
  Messages message_to_send;
  message_to_send.size = message.size();
  std::memcpy(&message_to_send.message, message.c_str(), message.size());
  socket.send(asio::buffer(&header, sizeof(header)));
  socket.send(asio::buffer(&message_to_send, sizeof(message_to_send)));
}

/**
 * @brief This function will handle the client.
 * @return void
 * @param socket The socket that will be used to send and receive data from the client.
 * @param server_data The server data that will be used to add the client to the server's list.
 * @see void receive_tcp_server(Header header, tcp::socket &socket)
 * @see void send_tcp_server(Header header, tcp::socket &socket, std::string message)
 * @details This function will handle the client, it will receive data from the client and send data to the client.
*/

void handle_client(std::shared_ptr<tcp::socket> socket, Server& server_data)
{
  std::cout << "Accepted connection from " << socket->remote_endpoint().address() << std::endl;

  // Add the client to the server's list
  uint16_t client_id = server_data.get_nb_clients() + 1;
  server_data.add_client(server_data.get_nb_clients() + 1, socket);
  server_data.print_all_clients();
  server_data.new_client(client_id);

  // Loop to receive and send data
  while (true) {
    Header_client header;
    std::memset(&header, 0, sizeof(header));
    size_t len = socket->read_some(asio::buffer(&header, sizeof(Header_client)));
    receive_tcp_server(header, *socket);
    std::cout << "Enter message to send: ";
    std::string message;
    std::getline(std::cin, message);
    std::memset(&header, 0, sizeof(header));
    Header_server header_server;
    header_server.id = 1;
    send_tcp_server(header_server, *socket, message);
  }
}

/**
 * @brief This function will launch the tcp server.
 * @return void
 * @param void
 * @see void handle_client(tcp::socket socket)
 * @details This function will launch the tcp server, it will create one thread, a thread that has the function handling the clients.
 * @details It will create a socket and an acceptor, the acceptor will accept the connection from the client and the socket will be used to send and receive data from the client
 * @details The thread will be detached so it will be able to run in the background and the main thread will be able to continue.
*/
void launch_tcp_server()
{
  io_context io_context;
  Server server_data;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12346));
  while (true) {
    std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
    acceptor.accept(*socket);
    std::thread t(handle_client, socket, std::ref(server_data));
    t.detach();
  }
}