/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** ClientInfo
*/

#include "../include/ClientInfo.hpp"

ClientInfo::ClientInfo(uint16_t id, std::shared_ptr<asio::ip::tcp::socket> socket) : id(id), hp(100), x(0), y(0), socket(socket)
{
}

// ClientInfo::ClientInfo(uint16_t id) : id(id), hp(0), x(0), y(0)
// {
// }

ClientInfo::~ClientInfo()
{
}

// ClientInfo::ClientInfo(const ClientInfo& other) : id(other.id), hp(other.hp), x(other.x), y(other.y), socket(other.socket)
// {
// }

ClientInfo& ClientInfo::operator=(const ClientInfo& other)
{
    id = other.id;
    hp = other.hp;
    x = other.x;
    y = other.y;
    socket = other.socket;
    return *this;
}

uint16_t ClientInfo::get_id() const { 
    return id;
}

uint16_t ClientInfo::get_hp() const {
    return hp;
}

void ClientInfo::set_hp(uint16_t new_hp) {
    hp = new_hp;
}

uint16_t ClientInfo::get_x() const {
    return x;
}

void ClientInfo::set_x(uint16_t new_x) {
    x = new_x;
}

uint16_t ClientInfo::get_y() const {
    return y;
}

void ClientInfo::set_y(uint16_t new_y) {
    y = new_y;
}

std::shared_ptr<asio::ip::tcp::socket> ClientInfo::get_socket() const {
    return socket;
}

void ClientInfo::print_info_clients() const {
    std::cout << "id: " << id << std::endl;
    std::cout << "hp: " << hp << std::endl;
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
}

void ClientInfo::set_socket(std::shared_ptr<asio::ip::tcp::socket> new_socket)
{
    socket = new_socket;
}

void ClientInfo::set_id(uint16_t new_id)
{
    id = new_id;
}