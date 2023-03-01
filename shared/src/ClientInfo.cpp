/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** ClientInfo
*/

#include "../include/ClientInfo.hpp"

ClientInfo::ClientInfo(uint16_t id, std::shared_ptr<asio::ip::tcp::socket> socket, uint16_t x, uint16_t y) : _id(id), _hp(100), _x(x), _y(y), _socket(socket)
{
}

ClientInfo::~ClientInfo()
{
}

ClientInfo& ClientInfo::operator=(const ClientInfo& other)
{
    _id = other._id;
    _hp = other._hp;
    _x = other._x;
    _y = other._y;
    _socket = other._socket;
    return *this;
}

uint16_t ClientInfo::get_id() const { 
    return _id;
}

uint16_t ClientInfo::get_hp() const {
    return _hp;
}

void ClientInfo::set_hp(uint16_t new_hp) {
    _hp = new_hp;
}

uint16_t ClientInfo::get_x() const {
    return _x;
}

void ClientInfo::set_x(uint16_t new_x) {
    _x = new_x;
}

uint16_t ClientInfo::get_y() const {
    return _y;
}

void ClientInfo::set_y(uint16_t new_y) {
    _y = new_y;
}

std::shared_ptr<asio::ip::tcp::socket> ClientInfo::get_socket() const {
    return _socket;
}

void ClientInfo::print_info_clients() const {
    std::cout << "id: " << _id << std::endl;
    std::cout << "hp: " << _hp << std::endl;
    std::cout << "x: " << _x << std::endl;
    std::cout << "y: " << _y << std::endl;
}

void ClientInfo::set_socket(std::shared_ptr<asio::ip::tcp::socket> new_socket)
{
    _socket = new_socket;
}

void ClientInfo::set_id(uint16_t new_id)
{
    _id = new_id;
}