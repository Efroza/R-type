/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parsing
*/

#ifndef PARSING_HPP_
#define PARSING_HPP_

#include <exception>
#include "Parsor.hpp"
#include "../ParseComponent/IParseComponent.hpp"
#include "handling_interaction.hpp"
#include "handling_component_system.hpp"
#include "../Include/registry.hpp"

class parsing
{
    public:
        parsing(registry &registre, data &daatabase, std::vector<std::string> const &config_files);
        ~parsing();
        void handle_config_files(handling_interaction &data_interactions, handling_component_system &cs_library);
        void handle_component_system(std::string const &name, Json::Value &entitie, entity_t &e);
        void handle_component_system_json(std::string const &name, Json::Value &entitie, entity_t &e, IComponentSystem *cs_value);

    private:
        void config_file(Parsor &pars);
        void handle_entites(Json::Value &entitie);
    private:
        registry *reg;
        data *db;
        std::vector<std::string> json_files;
        handling_interaction *data_interaction;
        handling_component_system *cs_data;
};

#endif /* !PARSING_HPP_ */