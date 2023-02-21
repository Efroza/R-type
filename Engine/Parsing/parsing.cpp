/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** main
*/

#include <exception>
#include "Parsor.hpp"
#include "IParseComponent.hpp"
#include "handling_interaction.hpp"

#include "parsing.hpp"

#include "registry.hpp"
#include "parse_position.hpp"
#include "parse_draw.hpp"
#include "parse_image.hpp"
#include "parse_rect.hpp"
#include "parse_animation.hpp"
#include "parse_interaction.hpp"

static std::unordered_map<std::string, std::function<IParseComponent *()>> const map = {
    {"position", [](){return new parse_component::position();}},
    {"image", [](){return new parse_component::image();}},
    {"draw", [](){return new parse_component::draw();}},
    {"rect", [](){return new parse_component::rect();}},
    {"animation", [](){return new parse_component::animation();}},
    {"interaction", [](){return new parse_component::interaction();}}
};

parsing::parsing(registry &registre, data &daatabase, std::vector<std::string> const &config_files)
: reg(&registre)
, db(&daatabase)
, json_files(config_files)
{
}

parsing::~parsing()
{
}

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

void parsing::config_file(Parsor &pars)
{
    Json::Value &json = pars.getJson();

    for (auto &name : json.getMemberNames()) {
        if (json[name].isObject()) {
            handle_entites(json[name]);
        }
    }
}

void parsing::handle_config_files(handling_interaction &data_interactions)
{
    data_interaction = &data_interactions;
    if (reg == nullptr || db == nullptr)
        return;
    for (auto &file : json_files) {
        try {
            Parsor pars(file);
            config_file(pars);
        } catch (std::exception const &e) {
            std::cout << file << ' ' << e.what() << std::endl;
        }
    }

}

void parsing::handle_entites(Json::Value &entitie)
{
    if (reg == nullptr || db == nullptr || data_interaction == nullptr)
        return;
    entity_t entity = reg->spawn_entity();

    for (auto &name : entitie.getMemberNames())
    {
        if (map.find(name) == map.end())
            continue;
        std::unique_ptr<IParseComponent> component(map.at(name)());
        AParseInteraction *interaction = dynamic_cast<AParseInteraction *>(component.get());
        if (interaction)
            interaction->set_interaction(*data_interaction);
        if (component->number_arguments_needed() != 0)
        {
            if (arguments_is_set(component.get(), entitie[name], *reg, *db))
                component->load_component(entity, *reg, *db, entitie[name]);
            continue;
        }
        if (entitie[name].isBool() && entitie[name].asBool() == false)
            continue;
        component->load_component(entity, *reg, *db, entitie[name]);
    }
}