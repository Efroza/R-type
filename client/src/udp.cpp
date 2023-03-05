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
    Messages response = {0};
    Position position = {0};

    bool dog = false;
    for (auto &i : _drawables) {
        if (i->getName() == std::to_string(header.id)) {
            std::cout << "G TROUVÉ" << std::endl;
            dog = true;
        }
    }
    if (!dog) {
        _drawables.push_back(std::make_shared<Drawable>(std::to_string(header.id), "./Engine/Image/spaceship_jet.png", std::pair<int, int>(200, 176), std::pair<int, int>(200, 200)));
    }
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
    std::cout << "DRAWABLE.SIZE: " << _drawables.size() << std::endl;
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
        Header header = {0};
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
    // send_data_client_udp(socket, server_endpoint); // Send to server
    // receive_thread.join();

    // socket.async_read_until(asio::buffer(&message[0], message.size()), server_endpoint,
    //     std::bind(&Client::_manage_receive, std::placeholders::_1, std::placeholders::_2, std::ref(message)));

    // io_context.run_one();

    events_e event = NONE;
    _libGraphic->initialize(1920, 1080, "Rtype");
    while (_playing) {
        event = _libGraphic->pollEvent();
        if (event == events_e::CLOSE) {
            _playing = false;
        } else if (event == events_e::ENTER) {
            std::cout << "ENTER\n";
        } else if (event == events_e::KEY_LEFT) {
            std::cout << "KEY_LEFT\n";
        } else if (event == events_e::KEY_RIGHT) {
            std::cout << "KEY_RIGHT\n";
        } else if (event == events_e::ESCAPE) {
            std::cout << "ESCAPE\n";
            _playing = false;
        } else if (event == events_e::KEY_DOWN) {
            std::cout << "KEY_DOWN\n";
        } else if (event == events_e::KEY_UP) {
            std::cout << "KEY_UP\n";
        }
        _libGraphic->clearWindow();
        switch (_scene) {
        case scene_e::HOME:
            _manageEventMenuHome(event);
            for (auto &i : _homeMenuDrawables) {
                _libGraphic->draw(i, i->getPosition());
            }
            break;
        // case scene_e::NETWORK_MENU:
        //     _manageEventMenuNetwork(event);
        //     for (auto &i : _networkMenuDrawables) {
        //         if (i->getName() == "text-selected-host") {
        //             i->setStr(_host);
        //         } else if (i->getName() == "text-selected-ip") {
        //             i->setStr(_ip);
        //         }
        //         _libGraphic->draw(i, i->getPosition());
        //     }
        //     break;
        case scene_e::GAME:
            // There send input to server
            _manageGameEvent(event, socket, server_endpoint);

            // Here add function that receive en manage data from server
            // If server send new entity info => add new Drawable with info inside, first param called name == entity's id
            // If server send position info => use getName to get your entity and update what server said
            // _manage_receive(socket);

            //draw all entities each frames using their positions
            for (auto &i : _drawables) {
                // this if is just for test, remove when server/client avec working
                if (i->getName() == "player") {
                    auto j = i->getPosition();
                    i->setPosition({j.first, j.second - 1});
                }
                _libGraphic->draw(i, i->getPosition());
            }
            break;
        default:
            break;
        }
        _libGraphic->refreshWindow();
        event = NONE;
    }
    _libGraphic->destroy();
    receive_thread.join();
}


void Client::loadLib(const std::string &filepath)
{
    #ifdef _WIN32 // Windows
    HINSTANCE handle = LoadLibrary(filepath.c_str());
    if (!handle) {
        throw std::runtime_error("Error LoadLibrary: " + std::to_string(GetLastError()));
    }
    IGraphic *(*funcPtr)() = reinterpret_cast<IGraphic *(*)()>(GetProcAddress(handle, "createGraphLib"));
    if (!funcPtr) {
        throw std::invalid_argument(std::string("Invalid lib: ") + std::to_string(GetLastError()));
    }
    #else // Linux
    void *handle = dlopen(filepath.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("Error dlopen: " + std::string(dlerror()));
    }
    IGraphic *(*funcPtr)() = reinterpret_cast<IGraphic *(*)()>(dlsym(handle, "createGraphLib"));
    if (!funcPtr) {
        throw std::invalid_argument(std::string("Invalid lib: ") + dlerror());
    }
    #endif

    auto a = std::function<IGraphic * ()>(funcPtr);
    _libGraphic.reset(std::move(a()));
    if (_libGraphic.get() == nullptr) {
        throw std::runtime_error("Error during lib loading");
    }
}

void Client::_manageEventMenuHome(events_e event)
{
    static int homeMenuIndex = 0;

    if (event == events_e::KEY_DOWN && homeMenuIndex < 1) {
        homeMenuIndex += 1;
        _playBtn->setColor(WHITE);
        _exitBtn->setColor(RED);
    } else if (event == events_e::KEY_UP && homeMenuIndex > 0) {
        homeMenuIndex -= 1;
        _playBtn->setColor(RED);
        _exitBtn->setColor(WHITE);
    } else if (event == events_e::ENTER) {
        if (homeMenuIndex == 0) {
            // _scene = scene_e::NETWORK_MENU;
            _scene = scene_e::GAME;
        } else if (homeMenuIndex == 1) {
            _playing = false;
        }
    }
}

void Client::_manageGameEvent(events_e event, udp::socket& socket, udp::endpoint& server_endpoint)
{
    Header header_to_send = {0};
    Position pos = {0};
    header_to_send.data_type = POSITION;
    pos.x = 1;
    pos.y = 2;
    // Send event info to server here
    if (event != events_e::NONE) {
        socket.send_to(asio::buffer(&header_to_send, sizeof(header_to_send)), server_endpoint);
        socket.send_to(asio::buffer(&pos, sizeof(pos)), server_endpoint);
        // send_struct_client_udp(socket, server_endpoint, "1,1");
    }

}

void Client::_manage_receive(const asio::error_code& error, std::size_t caca)
{
    std::cout << "ON A READ\n";
    char asas[1024];
    std::cout.write(asas, caca);
    std::cout << asas << std::endl;
    // Header header = {0};
    // udp::endpoint sender_endpoint;
    // asio::error_code ec;
    // Position position = {0};

    // size_t bytes_received = socket.receive_from(asio::buffer(&header, sizeof(Header)), sender_endpoint, 0, ec);
    // if (header.data_type == POSITION) {
    //     socket.receive_from(asio::buffer(&position, sizeof(Position)), sender_endpoint, 0, ec);
    //     std::cout << "POSITION from server: x: " << position.x << " y: " << position.y << " id: "<< header.id << std::endl;
    // }
}