/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** headers
*/

#ifndef HEADERS_HPP_
#define HEADERS_HPP_

#include <iostream>

enum Type {
    POSITION = 0,
    MESSAGE = 1,
};

enum Client_data {
    CONNECTED = 0,
    DIRECTION = 1,
    SPEED = 2,
    DISCONNECTED = 3,
};

enum Server_data {
    START = 0,
    ENNEMY = 1,
    DEAD = 2,
    LOSE = 3,
    WIN = 4,
    HIT = 5,
    ENNEMY_DEAD = 6,
    BONUS = 7,
};

struct Header {
    uint32_t id;
    Type data_type;
};

struct Direction {
    Direction_enum direction;
};

enum Direction_enum {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
};
struct Connected {
    std::vector<uint16_t> clients_id;
};

struct Speed {
    uint32_t speed;
};

struct Ennemy {
    uint32_t x;
    uint32_t y;
    uint32_t speed;
};

struct Hit {
    uint32_t hp;
};

struct ennemy_dead {
    uint32_t x;
    uint32_t y;
};

#endif /* !HEADERS_HPP_ */