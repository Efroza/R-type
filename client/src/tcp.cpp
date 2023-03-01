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
 * @brief Create the main class of the client side
 * @param host represents the host of the server
 * @param port represents the port of the server
 * @return void
 * @see Client::async_tcp_client(const asio::error_code& ec)
 * @details Create the main class of the client side
*/
Client::Client(const std::string& host, const std::string& port) : _host(host), _port(port)
{
    asio::io_context io_context;
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, port);

    _socket = std::make_unique<tcp::socket>(io_context);
    _client_info.set_socket(_socket);
    asio::async_connect(*_socket, endpoints,
        [&](const asio::error_code& ec, tcp::endpoint) {
            async_tcp_client(ec);
        });
    io_context.run();
}

Client::~Client()
{
}

/**
 * @brief This function will make the transition between tcp and udp (lobby and game)
 * @return void
 * @details This function will make the transition between tcp and udp (lobby and game)
*/
void Client::launch_game() {
    Header_client header_client;
    header_client.data_type = PREPARE_UDP;
    header_client.id = _client_info.get_id();
    _socket->send(asio::buffer(&header_client, sizeof(header_client)));

    Header_server header_server;
    std::memset(&header_server, 0, sizeof(Header_server));
    std::size_t bytes_received = _socket->receive(asio::buffer(&header_server, sizeof(Header_server)));
    if (bytes_received != sizeof(Header_server)) {
        std::cout << "Error while receiving data" << std::endl;
        return;
    }
    if (header_server.data_type == UDP) {
        std::cout << "Launching game on port : "<< header_server.id << std::endl;
        async_udp_client(_host, std::to_string(header_server.id));
    }
}

/**
 * @brief This function will get every clients that are connected to the lobby
 * @return void
 * @param header the header of the data to know the type of data
 * @details This function will read the data that was sent from the server and will keep it in a vector of clientInfo.
*/
void Client::start_game(Header_server header) {
    std::cout << "Game will start shortly" << std::endl;
    for (std::size_t i = 0; i < header.id; i++) {
        Start start;
        std::memset(&start, 0, sizeof(Start));
        std::size_t bytes_received = _socket->receive(asio::buffer(&start, sizeof(Start)));
        if (bytes_received != sizeof(Start)) {
            std::cout << "Error while receiving data" << std::endl;
            continue;
        }
        ClientInfo* client_info = new ClientInfo;
        std::memcpy(client_info, &start.client_info, sizeof(ClientInfo));
        if (client_info->get_id() == _client_info.get_id()) {
            _client_info.set_x(client_info->get_x());
            _client_info.set_y(client_info->get_y());
        } else {
            _other_clients.push_back(client_info);
        }
        std::memset(&start, 0, sizeof(Start));
    }
    std::cout << "I am client : " << _client_info.get_id() << " and my position is : " << _client_info.get_x() << " " << _client_info.get_y() << std::endl;
    for (auto &client : _other_clients) {
        std::cout << "Client : " << client->get_id() << " position is : " << client->get_x() << " " << client->get_y() << std::endl;
    }
    // Envoyer les infos au graphique => Position de chaque joueur avec id => client = client_info, les autres clients = _other_clients
    launch_game();
}

/**
 * @brief This function will translate the data received from the server.
 * @return void
 * @param header the header of the data to know the type of data
 * @details This function will read the data that was sent from the server and will print it.
 * @details It creates two struct one if it is a position and another one if it is a message.
 * @details Depending of the data type it will print the data.
*/
void Client::receive_tcp_client(Header_server header) {
    switch (header.data_type) {
        case MESSAGESS : {
            Messages message;
            _socket->receive(asio::buffer(&message, sizeof(Messages)));
            std::cout << "Received from server " << header.id << ": " << message.size << " ";
            std::cout.write(message.message, message.size) << std::endl;
            break;
        }
        case START : { // Start game graphique
            start_game(header);
            break;
        }
        default : {
            std::cout << "Wrong data type" << std::endl;
            break;
        }
    }
}

/**
 * @brief This function will send data to the server.
 * @return void
 * @param header the header of the data to know the type of data
 * @param message the message to send to the server
 * @details This function will send data to the server.
 * @details It will create a header with a data type depending of the message.
 * @details It will also create a struct depending of the data type.
 * @details It will send the header and the struct to the server.
 * @details If the message contains a comma it will be a position and if not, it will be a message.
 */
void Client::send_tcp_client(Header_client header, std::string message) {
    if (header.data_type == LOBBY) {
        _socket->send(asio::buffer(&header, sizeof(header)));
        return;
    }
    Messages message_to_send;
    message_to_send.size = message.size();
    std::memcpy(&message_to_send.message, message.c_str(), message.size());
    _socket->send(asio::buffer(&header, sizeof(header)));
    _socket->send(asio::buffer(&message_to_send, sizeof(message_to_send)));
}

/**
 * @brief This function will ask the user to enter the number of players he wants in the lobby before the game starts.
 * @return void
 * @details This function will ask the user to enter the number of players he wants in the lobby before the game starts and will then send that number to the server.
*/
void Client::inGame() {
    // Ask the user to enter the number of players he wants in the lobby before the game starts
    std::cout << "Enter number players lobby" << std::endl;
    std::string number_players;
    std::getline(std::cin, number_players);
    // Check if number_players is an int
    for (char const &tmp : number_players) {
        if (std::isdigit(tmp) == 0) {
            std::cout << "Wrong number of players" << std::endl;
            inGame();
            return;
        }
    }
    if (std::stoi(number_players) == 0 || std::stoi(number_players) > 4) {
        std::cout << "Wrong number of players" << std::endl;
        inGame();
        return;
    }
    Header_client header_client;
    header_client.id = std::stoi(number_players);
    header_client.data_type = LOBBY;
    send_tcp_client(header_client, number_players);
    _in_game = true;
}

/**
 * @brief This function will connect the client to the server and check if a lobby exist on this port.
 * @return void
 * @param ec the error code
 * @details This function will connect the client to the server and check if a lobby exist on this port, if yes it will ask the user if he wants to join the lobby, if not it will create a new lobby. @see inGame() and @see inLobby()
*/
void Client::connect_to_server(const asio::error_code& ec)
{
    std::cout << "Connected to the server via TCP." << std::endl;
    Header_client tmp_header;
    tmp_header.id = 0;
    tmp_header.data_type = CONNECTED;
    _socket->send(asio::buffer(&tmp_header, sizeof(tmp_header)));
    // Lancer le graphique connecter au serveur

    if (!ec) {
        Header_server tmp_header_server;
        _socket->receive(asio::buffer(&tmp_header_server, sizeof(tmp_header_server)));
        _client_info.set_id(tmp_header_server.id);
        std::cout << "Your id is : " << _client_info.get_id() << std::endl;
            if (tmp_header_server.data_type == LOBBYS) {
                Connection connection;
                _socket->receive(asio::buffer(&connection, sizeof(connection)));
                if (connection.id_lobby != 0) {
                    _in_game = true;
                    _lobby_created = true;
                    std::cout << "You are in the lobby that will wait for " << connection.id_lobby << " players before starting" << std::endl;
                } else {
                    std::cout << "You are not in a lobby" << std::endl;
                }
        }
    }
}

/**
 * @brief This function will be called if a lobby already exist on the port the client is trying to connect to.
 * @return void
 * @details This function will be called if a lobby already exist, and will ask the user if he wants to join the lobby, if not it will disconnect the client.
*/
void Client::inLobby()
{
    // Bouton oui et bouton non
    std::cout << "Lobby already exist do you want to join ?" << std::endl;
    std::string answer;
    std::getline(std::cin, answer);
    Header_client header_client;
    header_client.id = _client_info.get_id();
    if (answer != "yes" && answer != "y") {
        header_client.data_type = DISCONNECTED;
        _socket->send(asio::buffer(&header_client, sizeof(header_client)));
        exit(0);
    } else {
        header_client.data_type = LOBBY;
        _socket->send(asio::buffer(&header_client, sizeof(header_client)));
        // Display the lobby "Waiting for players..." and wait for the game to start
    }
    _lobby_created = false;
}

/**
 * @brief Launch a TCP client.
 * @param ec the error code
 * @return void
 * @see send_tcp_client(Header_client header, tcp::socket &socket, std::string message)
 * @see receive_tcp_client(Header_server header, tcp::socket &socket)
 * @details Launch an asynchronous TCP client.
 * @details The client can either send a message or a position.
 * 
 */
void Client::async_tcp_client(const asio::error_code& ec)
{
    if (!ec) {
        // Connected to the server successfully
        connect_to_server(ec);

        while (true) {
            if (!_in_game) {
                inGame();
            } else if (_lobby_created) {
                inLobby();
            } else {
                std::cout << "Enter message to send: ";
                std::string message;
                std::getline(std::cin, message);
                Header_client header_client;
                header_client.id = 1;
                header_client.data_type = MESSAGES;

                // Send the message to the server
                send_tcp_client(header_client, message);
            }

            // Receive a message from the server
            Header_server header_server;
            std::memset(&header_server, 0, sizeof(header_server));
            size_t bytes_received = _socket->receive(asio::buffer(&header_server, sizeof(header_server)));
            // If the server has sent a message, receive it
            if (!ec)
                receive_tcp_client(header_server);
        }
    }
}