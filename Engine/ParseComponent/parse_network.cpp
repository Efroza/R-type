/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_network
*/

#include "parse_network.hpp"
#include "../BaseComponent/network.hpp"

parse_component::network::network()
{
}

parse_component::network::~network()
{
}

void parse_component::network::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    reg.add_component<component::network>(e, std::move(component::network()));
}