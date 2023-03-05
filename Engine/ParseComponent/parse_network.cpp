/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_network
*/

#include "parse_network.hpp"
#include "../BaseComponent/network.hpp"

/**
 * @file parse_network.cpp
 */

parse_component::network::network()
{
}

parse_component::network::~network()
{
}

/**
 * @brief Load the component
 *
 * @param e Entity to add the component to
 * @param reg Registry to add the component to
 * @param db Database to add the component to
 * @param json Json object to load the component from
 */

void parse_component::network::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    reg.add_component<component::network>(e, std::move(component::network()));
}