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
#include "IParseComponent.hpp"
#include "handling_interaction.hpp"
#include "registry.hpp"

class parsing
{
    public:
        parsing(registry &registre, data &daatabase, std::vector<std::string> const &config_files);
        ~parsing();
        void handle_config_files(handling_interaction &data_interactions);

    private:
        void config_file(Parsor &pars);
        void handle_entites(Json::Value &entitie);
    private:
        registry *reg;
        data *db;
        std::vector<std::string> json_files;
        handling_interaction *data_interaction;
};

#endif /* !PARSING_HPP_ */