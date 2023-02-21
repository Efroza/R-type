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

class ClientInfo {
    public:
        ClientInfo(uint16_t id, std::shared_ptr<asio::ip::tcp::socket> socket);
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
    private:
        uint16_t id;
        uint16_t hp;
        uint16_t x;
        uint16_t y;
        std::shared_ptr<asio::ip::tcp::socket> socket;
};

#endif /* !CLIENTINFO_HPP_ */
