/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** handle_entity
*/

#ifndef HANDLE_ENTITY_HPP_
#define HANDLE_ENTITY_HPP_

#include <optional>
#include "registry.hpp"
#include "data.hpp"
#include "entity.hpp"
#include "position.hpp"

class handle_entity
{
    public:
        handle_entity(registry &reg, data &db, const std::string &image = "Image/spaceship_jet.png");
        ~handle_entity();
        void manage_entity(const component::position &pos, size_t id);
        void manage_entity(const component::position &pos, entity_t const &entity);
        void create_entity(const component::position &pos, size_t id);
        void modifies_entity(const component::position &pos, size_t id) noexcept;
        bool id_already_exist(size_t id) const noexcept;
        std::optional<entity_t> const &get_entity(size_t id) noexcept;

    private:
        registry *reg;
        data *db;
        std::string image;
        std::vector<entity_t> _entities;
        /* data */
};

#endif /* !HANDLE_ENTITY_HPP_ */
