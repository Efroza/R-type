/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** ClientInfo
*/

#ifndef CLIENTINFO_HPP_
#define CLIENTINFO_HPP_

#ifdef _WIN32
#include "../../framework.h"
#endif

#include <asio.hpp>
#include <iostream>
#include <algorithm>
#include <thread>
#include <vector>
#include <cstdint>
#include <cstring>
#include <map>
#include <stdint.h>

/**
 * @file ClientInfo.hpp
 */

/**
 * @brief Class that contains all the information about a client.
*/
class ClientInfo {
    public:
        ClientInfo() : _id(0), _hp(0), _x(0), _y(0) {};
        ClientInfo(uint16_t id, std::shared_ptr<asio::ip::tcp::socket> socket, uint16_t x, uint16_t y);
        ~ClientInfo();
        // ClientInfo(const ClientInfo& other);
        ClientInfo& operator=(const ClientInfo& other);

        uint16_t get_id() const;
        uint16_t get_hp() const;
        void set_hp(uint16_t new_hp);
        uint16_t get_x() const;
        void set_x(uint16_t new_x);
        uint16_t get_y() const;
        void set_y(uint16_t new_y);
        std::shared_ptr<asio::ip::tcp::socket> get_socket() const;
        void print_info_clients() const;
        void set_socket(std::shared_ptr<asio::ip::tcp::socket> new_socket);
        void set_id(uint16_t new_id);
    private:
        uint16_t _id;
        uint16_t _hp;
        uint16_t _x;
        uint16_t _y;
        std::shared_ptr<asio::ip::tcp::socket> _socket;
};

#endif /* !CLIENTINFO_HPP_ */
