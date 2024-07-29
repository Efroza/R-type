/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** step0
*/

#ifndef STEP0_HPP_
#define STEP0_HPP_

#include <iostream>

struct entity_t {
    size_t _id;
    entity_t(size_t id) : _id(id) {}
    entity_t(const entity_t &equal) : _id(equal._id) {}
    entity_t(entity_t &&equal) : _id(std::move(equal._id)) {}
    operator size_t() {
        return _id;
    }
    entity_t &operator = (const size_t &value)
    {
        this->_id = value;
        return *this;
    }
    entity_t &operator=(size_t &&value)
    {
        this->_id = std::move(value);
        return *this;
    }
    entity_t &operator=(size_t &value)
    {
        this->_id = value;
        return *this;
    }
    bool operator < (const size_t &value)
    {
        return value < _id;
    }
    bool operator > (const size_t &value)
    {
        return value > _id;
    }
};

#endif /* !STEP0_HPP_ */
