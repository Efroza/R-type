/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** handle_entity
*/

#ifndef HANDLE_ENTITY_HPP_
#define HANDLE_ENTITY_HPP_

#include "registry.hpp"
#include "data.hpp"
#include "entity.hpp"
#include "BaseComponent/position.hpp"

class handle_entity
{
    public:
        handle_entity(registry &reg, data &db);
        ~handle_entity();
        manage_entity(compoent::postion &pos, size_t id);

    private:
        std::vector<entity_t> _entities;
        /* data */
};

#endif /* !HANDLE_ENTITY_HPP_ */
