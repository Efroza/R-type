/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_image
*/

#include "parse_image.hpp"
#include "image.hpp"

parse_component::image::image()
{
    set_argument_needed<std::string>("file");
}

parse_component::image::~image()
{
}

void parse_component::image::load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const
{
    if (good_arg(json, "file") == false)
        return;
    std::string file = json["file"].asString();
    reg.add_component<component::image>(e, std::move(component::image(file, db, e)));
}