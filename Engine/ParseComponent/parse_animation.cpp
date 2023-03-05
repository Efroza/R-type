/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_animation
*/

#include "./parse_animation.hpp"
#include "../BaseComponent/animation.hpp"

/**
 * @file parse_animation.cpp
 *
 * @brief Parse animation component
 */

parse_component::animation::animation()
{
}

parse_component::animation::~animation()
{
}

/**
 * @brief Check if the json object has a time key
 *
 * @param json Reference to the json object
 * @return true if the json object has a time key and false otherwise
 */

bool got_time(Json::Value const &json)
{
    if (json.isObject() == false)
        return false;
    for (auto &name : json.getMemberNames())
    {
        if (name == "time")
            return true;
    }
    return false;
}

/**
 * @brief Load the animation component
 *
 * @param e Entity to load the component
 * @param reg Reference to the registry
 * @param db Reference to the data
 * @param json Reference to the json object
 */

void parse_component::animation::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    if (got_time(json) == false || json["time"].empty() || json["time"].isUInt() == false) {
        reg.add_component<component::animation>(e, std::move(component::animation()));
        return;
    }
    std::uint32_t time = json["time"].asUInt64();
    reg.add_component<component::animation>(e, std::move(component::animation(time)));
}