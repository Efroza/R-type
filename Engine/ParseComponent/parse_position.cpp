/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** position
*/

#include "parse_position.hpp"
#include "../BaseComponent/position.hpp"

/**
 * @file parse_position.cpp
 */

/**
 * @brief Construct a new parse component::position::position object
 *
 * @details Set the argument needed to load the component
 */

parse_component::position::position()
{
    set_argument_needed<int>("x");
    set_argument_needed<int>("y");
}

parse_component::position::~position()
{
}

/**
 * @brief Load the position component
 *
 * @param e Entity to load the component
 * @param reg Reference to the registry
 * @param db Reference to the data
 * @param json Reference to the json object
 */

void parse_component::position::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    if (json["x"].empty() || json["y"].empty() || json["x"].isUInt() == false || json["y"].isUInt() == false)
        return;
    std::uint32_t x = json["x"].asInt();
    std::uint32_t y = json["y"].asInt();
    reg.add_component<component::position>(e, std::move(component::position(x, y)));
}