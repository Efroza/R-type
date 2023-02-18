/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_rect
*/

#include "parse_rect.hpp"
#include "rect.hpp"

parse_component::rect::rect()
{
    set_argument_needed<int>("line");
    set_argument_needed<int>("cols");
}

parse_component::rect::~rect()
{
}

void parse_component::rect::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    if (good_arg(json, "line") == false || good_arg(json, "cols") == false)
        return;
    std::uint8_t line = json["line"].asInt();
    std::uint8_t cols = json["cols"].asInt();
    reg.add_component<component::rect>(e, std::move(component::rect(line, cols)));
}