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

struct Header {
    uint32_t id;
    Type data_type;
};

struct Position {
    uint32_t x;
    uint32_t y;
};

struct Messages {
    uint32_t size;
    char message[1024];
};

#endif /* !HEADERS_HPP_ */