/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** handle_entity
*/

#include "handle_entity.hpp"
#include "image.hpp"
#include "draw.hpp"

handle_entity::handle_entity(registry &reg, data &db, const std::string &image) : reg(&reg), db(&db), image(image)
{

}

handle_entity::~handle_entity()
{

}

bool handle_entity::id_already_exist(size_t id) const noexcept
{
    for (auto &entity : _entities)
        if (entity._id == id)
            return true;
    return false;
}

std::optional<entity_t> const &handle_entity::get_entity(size_t id) noexcept
{
    for (auto &entity : _entities)
        if (entity._id == id)
            return entity;
    return std::nullopt;
}

void handle_entity::create_entity(const component::position &pos, size_t id)
{
    if (id_already_exist(id))
        return;
    entity_t spaceship(id);
    reg->add_component<component::position>(spaceship, std::move(component::position(pos)));
    reg->add_component<component::image>(spaceship, std::move(component::image(image, *db, spaceship)));
    reg->add_component<component::draw>(spaceship, std::move(component::draw()));
    _entities.emplace_back(std::move(spaceship));
}

void handle_entity::modifies_entity(const component::position &pos, size_t id) noexcept
{
    const auto &entity = get_entity(id);
    if (entity)
        reg->add_component<component::position>(entity.value(), std::move(component::position(pos)));
}

void handle_entity::manage_entity(const component::position &pos, size_t id)
{
    if (id_already_exist(id))
        modifies_entity(pos, id);
    else
        create_entity(pos, id);
}

void handle_entity::manage_entity(const component::position &pos, entity_t const &entity)
{
    manage_entity(pos, entity._id);
}