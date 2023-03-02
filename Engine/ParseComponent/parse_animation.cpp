/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_animation
*/

#include "./parse_animation.hpp"
#include "../BaseComponent/animation.hpp"

parse_component::animation::animation()
{
}

parse_component::animation::~animation()
{
}

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

void parse_component::animation::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    if (got_time(json) == false || json["time"].empty() || json["time"].isUInt() == false) {
        reg.add_component<component::animation>(e, std::move(component::animation()));
        return;
    }
    std::uint32_t time = json["time"].asUInt64();
    reg.add_component<component::animation>(e, std::move(component::animation(time)));
}