/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** tcp
*/

#include "../include/server.hpp"

using asio::io_context;
using asio::ip::tcp;
using asio::buffer;

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
TCP_Server::TCP_Server(uint16_t port) : _port(port)
{
  start = std::thread(&TCP_Server::launch_tcp_server, this);
}

TCP_Server::~TCP_Server()
{
  start.join();
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
void TCP_Server::launch_tcp_server()
{
  io_context io_context;
  tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), _port));

  _port_udp = acceptor.local_endpoint().port() + 1;

  while (true) {
    std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
    acceptor.accept(*socket);
    std::thread handle(&TCP_Server::handle_client, this, socket, std::ref(server_data));
    handle.detach();
  }
}

/**
 * @brief This function will accept a new client and create a lobby.
 * @return void
 * @param socket The socket that will be used to send and receive data from the client.
 * @param server_data The server data that will be used to send data to the client.
 * @param client_id The id of the client that will be used to send data to the client.
 * @details This function will accept a new client and create a lobby if there is no lobby created on this port yet. If there is a lobby created it will send a message to the client to say that a lobby is already created.
*/
void TCP_Server::new_client_create_lobby(std::shared_ptr<tcp::socket> socket, Server& server_data, uint16_t client_id)
{
  Header_client tmp_header_client;
  std::memset(&tmp_header_client, 0, sizeof(tmp_header_client));
  socket->receive(buffer(&tmp_header_client, sizeof(tmp_header_client)));
  std::cout << "New client with id " << client_id << std::endl;
  Connection connection;
  Header_server header_server;
  header_server.id = client_id;
  header_server.data_type = LOBBYS;
  socket->send(asio::buffer(&header_server, sizeof(Header_server)));
  if (_lobby) {
    // Send messages to say that a lobby is already created
    connection.id_lobby = _nb_lobby;
    std::cout << "Lobby already created" << std::endl;
  } else {
    // Send messages to say that a lobby is not created
    connection.id_lobby = 0;
    std::cout << "Lobby not created" << std::endl;
  }
  socket->send(asio::buffer(&connection, sizeof(Connection)));
}

/**
 * @brief This function will handle the client.
 * @return void
 * @param socket The socket that will be used to send and receive data from the client.
 * @see void receive_tcp_server(Header_client header, tcp::socket &socket)
 * @see void send_tcp_server(Header_server header, tcp::socket &socket, std::string message)
 * @details This function will handle the client, it will receive data from the client and send data to the client.
*/
void TCP_Server::handle_client(std::shared_ptr<tcp::socket> socket, Server& server_data)
{
  std::cout << "Accepted connection from " << socket->remote_endpoint().address() << std::endl;

  // Add the client to the server's list
  uint16_t client_id = server_data.get_nb_clients() + 1;
  server_data.add_client(server_data.get_nb_clients() + 1, socket, last_x, 10);
  last_x += 10;
  server_data.print_all_clients();
  _nb_clients = server_data.get_nb_clients();

  // Create a lobby if there is no lobby
  new_client_create_lobby(socket, server_data, client_id);

  // Loop to receive and send data
  while (true) {
    Header_client header;
    std::memset(&header, 0, sizeof(header));
    size_t len = socket->read_some(asio::buffer(&header, sizeof(Header_client)));
    receive_tcp_server(header, *socket, server_data);
    if (_lobby) {
      std::cout << "Waiting for all players to join the lobby" << std::endl;
      while (_nb_clients != _nb_lobby)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      Header_client header_client_tmp;
      size_t len = socket->read_some(asio::buffer(&header_client_tmp, sizeof(Header_client)));
      if (len != sizeof(Header_client)) {
        std::cout << "Error: Header not received" << std::endl;
        return;
      }
      receive_tcp_server(header_client_tmp, *socket, server_data);
    }
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
void TCP_Server::send_tcp_server(Header_server header, tcp::socket &socket, std::string message) {
  header.id = 1;
  header.data_type = MESSAGESS;
  Messages message_to_send;
  message_to_send.size = message.size();
  std::memcpy(&message_to_send.message, message.c_str(), message.size());
  socket.send(asio::buffer(&header, sizeof(header)));
  socket.send(asio::buffer(&message_to_send, sizeof(message_to_send)));
}

/**
 * @brief This function will translate the data received from the client.
 * @return void
 * @param header the header of the data to know the type of data
 * @param socket the socket of the server to receive data from client
 * @details This function will read the data that was sent from the client and will print it.
 * @details It creates two struct one if it is a position and another one if it is a message.
 * @details Depending of the data type it will print the data.
*/
void TCP_Server::receive_tcp_server(Header_client header, tcp::socket &socket, Server& server_data) {
  switch (header.data_type) {
    case MESSAGES: {
      Messages message;
      socket.receive(asio::buffer(&message, sizeof(Messages)));
      std::cout << "Received from client " << header.id << ": " << message.size << " ";
      std::cout.write(message.message, message.size) << std::endl;
      break;
    }
    case LOBBY: {
      if (_lobby)
        std::cout << "Player " << header.id << " joined the lobby" << std::endl;
      else {
        _lobby = true;
        _nb_lobby = header.id;
      }
      _nb_clients = server_data.get_nb_clients();
      std::cout << "Waiting for " << _nb_lobby - _nb_clients << " players" << std::endl;
      if (_nb_clients == _nb_lobby) {
        std::cout << "All players have joined the lobby" << std::endl;
        server_data.print_all_clients();
        server_data.send_to_all_clients(START, server_data.get_nb_clients());
        // Faire une function pour set up les positions des clients => pour ce faire y'a besoin de la taille de la window
        server_data.send_vector_clients();
        Header_client header_client;
        socket.receive(asio::buffer(&header_client, sizeof(Header_client)));
        receive_tcp_server(header_client, socket, server_data);
      }
      break;
    }
    case DISCONNECTED :{
      std::cout << "Client " << header.id << " disconnected" << std::endl;
      server_data.remove_client(header.id);
      _nb_clients = server_data.get_nb_clients();
      server_data.print_all_clients();
      break;
    }
    case PREPARE_UDP : {
      std::cout << "Client has received data " << header.id << std::endl;
      Header_server header_server;
      header_server.id = _port_udp;
      header_server.data_type = UDP;
      socket.send(asio::buffer(&header_server, sizeof(header_server)));
    }
    default:
      std::cout << "Unknown data type" << std::endl;
      std::cout << "Data type: " << header.data_type << std::endl;
      std::cout << "ID: " << header.id << std::endl;
      break;
  }
}