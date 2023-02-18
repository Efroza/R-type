/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_draw
*/

#include "parse_draw.hpp"
#include "draw.hpp"

parse_component::draw::draw()
{
}

parse_component::draw::~draw()
{

}

void parse_component::draw::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    reg.add_component<component::draw>(e, std::move(component::draw()));
}