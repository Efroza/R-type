/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_image
*/

#include "parse_image.hpp"
#include "../BaseComponent/image.hpp"

/**
 * @file parse_image.cpp
 *
 */

/**
 * @brief Construct a new parse component::image::image object
 *
 * @details Set the argument needed to load the component
 */
parse_component::image::image()
{
    set_argument_needed<std::string>("file");
}

parse_component::image::~image()
{
}

/**
 * @brief Load the image component
 *
 * @param e Entity to load the component
 * @param reg Reference to the registry
 * @param db Reference to the data
 * @param json Reference to the json object
 */

void parse_component::image::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    if (good_arg(json, "file") == false)
        return;
    std::string file = json["file"].asString();
    reg.add_component<component::image>(e, std::move(component::image(file, db, e)));
}