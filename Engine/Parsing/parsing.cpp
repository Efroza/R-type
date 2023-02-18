/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** main
*/

#include <exception>
#include "Parsor.hpp"
#include "IParseComponent.hpp"
#include "registry.hpp"
#include "parse_position.hpp"
#include "parse_draw.hpp"
#include "parse_image.hpp"
#include "parse_rect.hpp"
#include "parse_animation.hpp"

static std::unordered_map<std::string, std::function<IParseComponent *()>> const map = {
    {"position", [](){return new parse_component::position();}},
    {"image", [](){return new parse_component::image();}},
    {"draw", [](){return new parse_component::draw();}},
    {"rect", [](){return new parse_component::rect();}},
    {"animation", [](){return new parse_component::animation();}},
};

static bool arguments_is_set(IParseComponent *component, Json::Value &json,registry &reg, data &db)
{
    IParseComponent::parse_map const &parser = component->argument_needed();

    for (auto &need_arg : parser)
        if (json[need_arg.first].empty()) {
            std::cerr << "error parsing argument " << need_arg.first << " not set in component " << component->get_name() << std::endl;
            return false;
        }
    return true;
}

static void handle_entites(Json::Value &entitie, registry &reg, data &db)
{
    entity_t entity = reg.spawn_entity();

    for (auto &name : entitie.getMemberNames())
    {
        if (map.find(name) == map.end())
            continue;
        std::unique_ptr<IParseComponent> component(map.at(name)());
        if (component->number_arguments_needed() != 0) {
            if (arguments_is_set(component.get(), entitie[name],reg, db))
                component->load_component(entity, reg, db, entitie[name]);
            continue;
        }
        if (entitie[name].isBool() && entitie[name].asBool() == false)
            continue;
        component->load_component(entity, reg, db, entitie[name]);
    }
}

static void config_file(Parsor &pars, registry &reg, data &db)
{
    Json::Value &json = pars.getJson();

    for (auto &name : json.getMemberNames()) {
        if (json[name].isObject()) {
            handle_entites(json[name], reg, db);
        }
    }
}

void handle_config_files(std::vector<std::string> const &files, registry &reg, data &db)
{
    for (auto &file : files)
    {
        try {
            Parsor pars(file);
            config_file(pars, reg, db);
        } catch (std::exception const &e) {
            std::cout << file << ' ' << e.what() << std::endl;
        }
    }
}