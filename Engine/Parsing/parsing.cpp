/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** main
*/

#include <exception>
#include "Parsor.hpp"
#include "../ParseComponent/IParseComponent.hpp"
#include "../Parsing/handling_interaction.hpp"

#include "parsing.hpp"

#include "../Include/registry.hpp"
#include "../ParseComponent/parse_position.hpp"
#include "../ParseComponent/parse_image.hpp"
#include "../ParseComponent/parse_rect.hpp"
#include "../ParseComponent/parse_animation.hpp"
#include "../ParseComponent/parse_interaction.hpp"
#include "../ParseComponent/parse_network.hpp"

/**
 * @file parsing.cpp
 */

/**
 * @brief Map of all the component system that can be parsed.
 */

static std::unordered_map<std::string, std::function<IParseComponent *()>> const map = {
    {"position", [](){return new parse_component::position();}},
    {"image", [](){return new parse_component::image();}},
    {"rect", [](){return new parse_component::rect();}},
    {"animation", [](){return new parse_component::animation();}},
    {"interaction", [](){return new parse_component::interaction();}},
    {"network", [](){return new parse_component::network();}},
};

/**
 * @brief Construct a new parsing::parsing object
 *
 * @param registre Registry of the engine, used to contain all the component system.
 * @param daatabase To store all the data.
 * @param config_files Name of the JSON files to parse.
 */
parsing::parsing(registry &registre, data &daatabase, std::vector<std::string> const &config_files)
: reg(&registre)
, db(&daatabase)
, json_files(config_files)
, data_interaction(nullptr)
, cs_data(nullptr)
{
}

parsing::~parsing()
{
}

/**
 * @brief Check if all the arguments needed by the component system are set.
 *
 * @param component Component system to check.
 * @param json JSON file to check.
 * @param reg Registry of the engine.
 * @param db Database of the engine.
 * @return true All the arguments are set.
 * @return false One or more arguments are not set.
 */

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

/**
 * @brief Parse the JSON file.
 *
 * @param pars Parsor object to parse the JSON file.
 */

void parsing::config_file(Parsor &pars)
{
    Json::Value &json = pars.getJson();

    for (auto &name : json.getMemberNames()) {
        if (json[name].isObject()) {
            handle_entites(json[name]);
        }
    }
}

/**
 * @brief Parse all the JSON files.
 *
 * @param data_interactions Interaction of the engine.
 * @param cs_library Component system library of the engine.
 * @details Manage the parsing of all the JSON files and check errors.
 */

void parsing::handle_config_files(handling_interaction &data_interactions, handling_component_system &cs_library)
{
    data_interaction = &data_interactions;
    cs_data = &cs_library;

    cs_library.load_all_component(*reg);
    cs_library.load_all_system(*reg);
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

/**
 * @brief Parse a component system.
 *
 * @param name Name of the component system.
 * @param entitie JSON file to parse.
 * @param e Entity to add the component system.
 * @param cs_value Component system to parse.
 */

void parsing::handle_component_system_json(std::string const &name, Json::Value &entitie, entity_t &e, IComponentSystem *cs_value)
{
    if (cs_value == nullptr)
        return;
    IParseComponent *parse_component = dynamic_cast<IParseComponent *>(cs_value);
    if (parse_component == nullptr)
        return;
    if (parse_component->number_arguments_needed() != 0 && arguments_is_set(parse_component, entitie[name], *reg, *db)) {
        parse_component->load_component(e, *reg, *db, entitie[name]);
        std::cerr << name << std::endl;
        return;
    }
    if (entitie[name].isBool() && entitie[name].asBool() == false)
        return;
    parse_component->load_component(e, *reg, *db, entitie[name]);
}

/**
 * @brief Parse all the component system of an entity.
 *
 * @param name Name of the component system.
 * @param entitie JSON file to parse.
 * @param e Entity to add the component system.
 */

void parsing::handle_component_system(std::string const &name, Json::Value &entitie, entity_t &e)
{
    if (cs_data == nullptr)
        return;
    if (cs_data->name_in_lib(name) == false)
        return;
    IComponentSystem *cs_value = cs_data->get_component_system(name);
    if (cs_value == nullptr)
        return;
    cs_value->add_entity_component(*reg, e);
    IParseComponent *parse_component = dynamic_cast<IParseComponent *>(cs_value);
    handle_component_system_json(name, entitie, e, cs_value);
    return;
}

/**
 * @brief Parse an entity.
 *
 * @param entitie JSON file to parse.
 */

void parsing::handle_entites(Json::Value &entitie)
{
    if (reg == nullptr || db == nullptr || data_interaction == nullptr)
        return;
    entity_t entity = reg->spawn_entity();

    for (auto &name : entitie.getMemberNames())
    {
        if (map.find(name) == map.end()) {
            handle_component_system(name, entitie, entity);
            continue;
        }
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