/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** main
*/

#include <unistd.h>
#include <SFML/Window.hpp>
#include <functional>
#include <dlfcn.h>
#include <memory>
// #include "IGraphic.hpp"
#include "parsing.hpp"
#include "systems.hpp"
#include "draw.hpp"
#include "rect.hpp"
#include "systems.hpp"
#include "interaction.hpp"
#include "interactive.hpp"
#include "handling_interaction.hpp"
#include "Yaml.hpp"

void game(registry &reg, data &db, Yaml &yaml)
{
    load_system(reg);
    load_component(reg);
    std::vector<std::string> config = yaml.get("config_json");
    std::vector<std::string> interaction_config = yaml.get("config_interaction");
    handling_component_system cs_lib = yaml.get("config_component_system");
    handling_interaction interaction(interaction_config);
    parsing handling_parse(reg, db, config);
    handling_parse.handle_config_files(interaction, cs_lib);
    while (true)
        reg.run_systems();
}

void init_databases(data &db)
{

    db.add_list_data<sf::Texture>();

    //network.set_protocol(POSITION)
    //network.send<component::position>()
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    try {
        data db;
        Yaml yaml(av[1]);
        if (yaml.data_exist("config_json") == false || yaml.data_exist("config_interaction") == false)
            throw std::runtime_error("config_json or config_interaction not set in yaml");
        registry reg;
        init_databases(db);
        game(reg, db, yaml);
    } catch(std::exception const &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
}