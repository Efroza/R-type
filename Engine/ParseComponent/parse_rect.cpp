/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_rect
*/

#include "parse_rect.hpp"
#include "../BaseComponent/rect.hpp"

/**
 * @file parse_rect.cpp
 */

/**
 * @brief Construct a new parse component::rect::rect object
 *
 * @details Set the argument needed to load the component
 */

parse_component::rect::rect()
{
    set_argument_needed<int>("line");
    set_argument_needed<int>("cols");
}

parse_component::rect::~rect()
{
}

/**
 * @brief Load the rect component
 *
 * @param e Entity to load the component
 * @param reg Reference to the registry
 * @param db Reference to the data
 * @param json Reference to the json object
 */

void parse_component::rect::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    if (good_arg(json, "line") == false || good_arg(json, "cols") == false)
        return;
    std::uint8_t line = json["line"].asInt();
    std::uint8_t cols = json["cols"].asInt();
    reg.add_component<component::rect>(e, std::move(component::rect(line, cols)));
}