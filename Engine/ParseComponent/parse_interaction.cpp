/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_interaction
*/

#include "parse_interaction.hpp"
#include "../BaseComponent/interaction.hpp"

// right 72
// left 71
// up 73
// down 74

/**
 * @file parse_interaction.cpp
 */

parse_component::interaction::interaction()
{
}

parse_component::interaction::~interaction()
{
}

/**
 * @brief Check if the json object has the key
 *
 * @param json Reference to the json object
 * @return true if the json object has the key and false otherwise
 */

static bool got_key(Json::Value const &json, std::string const &key)
{
    if (json.isObject() == false)
        return false;
    for (auto &name : json.getMemberNames())
    {
        if (name == key)
            return true;
    }
    return false;
}

/**
 * @brief Check if there is a digit in the string
 *
 * @param str String to check
 * @return true if there is a digit in the string and false otherwise
 */

bool is_digit(std::string const &str)
{
    for (auto &c : str) {
        if (c >= '0' && c <= '9')
            continue;
        return false;
    }
    return true;
}

/**
 * @brief Handling the string interaction
 *
 * @param e The entity to load the component
 * @param reg The registry of the game
 * @param key The key of the interaction
 * @param interaction_name The name of the interaction
 * @details This function will load the interaction component of the entity
 */

void parse_component::interaction::handling_string_interaction(entity_t const &e, registry &reg, std::string const &key, std::string const &interaction_name) const noexcept
{
    if (_interaction == nullptr || is_digit(key) == false)
        return;
    int key_digit = std::atoi(key.c_str());
    if (key_digit < 0)
        return;
    ILoad_Interaction const *load_interaction = _interaction->get_interaction(interaction_name);
    if (load_interaction == nullptr) {
        std::cerr << "unknow interaction: " << interaction_name << std::endl;
        return;
    }
    component::interaction interact;
    sparse_array<component::interaction> &tab = reg.get_components<component::interaction>();
    if (e._id < tab.size() && tab[e._id]) {
        tab[e._id].value().new_interaction(key_digit, load_interaction->get_function());
        return;
    }
    interact.new_interaction(key_digit, load_interaction->get_function());
    reg.add_component<component::interaction>(e, std::move(interact));
}

/**
 * @brief Load the interaction component
 *
 * @param e The entity to load the component
 * @param reg The registry of the game
 * @param db The database of the game
 * @param json The json object to load the component
 * @details This function will load the interaction component of the entity
 */

void parse_component::interaction::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    if (_interaction == nullptr)
        return;
    if (json.isObject() == false)
        return;
    for (auto &name : json.getMemberNames())
        if (json[name].isString())
            handling_string_interaction(e, reg, name, json[name].asString());
}