/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** headers
*/

#ifndef HEADERS_HPP_
#define HEADERS_HPP_

#include <iostream>
#include <vector>

enum Type {
    POSITION = 0,
    MESSAGE = 1,
};

enum Client_data {
    CONNECTED = 0, // TCP
    DIRECTION = 1, // UDP
    SPEED = 2, // UDP
    DISCONNECTED = 3, // TCP and UDP
    LOBBY = 4, // TCP
    MESSAGES = 5,
};

enum Server_data {
    START = 0, // TCP 
    ENNEMY = 1, // UDP
    DEAD = 2, // UDP
    LOSE = 3, // UDP
    WIN = 4, // UDP
    HIT = 5, // UDP
    ENNEMY_DEAD = 6, // UDP
    BONUS = 7, // UDP
    NEW_CLIENT = 8, // TCP
    ALREADY_IN_GAME = 9, // TCP
    MESSAGESS = 10, // TCP
    LOBBYS = 11, // TCP
};

struct Header {
    uint16_t id;
    Type data_type;
};

struct Messages {
    char message[1024];
    uint16_t size;
};

struct Header_server {
    uint16_t id;
    Server_data data_type;
};

struct Header_client {
    uint16_t id;
    Client_data data_type;
};

enum Direction_enum {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
};

struct Direction {
    Direction_enum direction;
};

struct Connection {
    uint16_t id_lobby;
};
struct Connected {
    std::vector<uint16_t> clients_id;
};

struct Speed {
    uint16_t speed;
};

struct Ennemy {
    uint16_t x;
    uint16_t y;
    uint16_t speed;
};

struct Hit {
    uint16_t hp;
};

struct ennemy_dead {
    uint16_t x;
    uint16_t y;
};

struct Position {
    uint16_t x;
    uint16_t y;
};

struct New_client {
    uint16_t id;
};

#endif /* !HEADERS_HPP_ */