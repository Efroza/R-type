/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** main
*/

#ifdef _unix_
#include <unistd.h>
#include <dlfcn.h>
#endif

#include <SFML/Window.hpp>
#include <functional>
#include <memory>
// #include "IGraphic.hpp"
#include "../Parsing/parsing.hpp"
#include "../Include/systems.hpp"
#include "../ComponentSystem/draw.hpp"
#include "../BaseComponent/rect.hpp"
#include "../BaseComponent/interaction.hpp"
#include "../Include/interactive.hpp"
#include "../Parsing/handling_interaction.hpp"  
#include "../Parsing/Yaml.hpp"

/**
 * @file main.cpp
 */

/**
 * @brief Create the gameplay.
 *
 * @param reg Container of all the systems and components.
 * @param db Container of all the data (textures, sounds, etc...)
 * @param yaml File containing the configuration of the game.
 */

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

/**
 * @brief Initialize the databases.
 *
 * @param db Container of all the data (textures, sounds, etc...)
 */

void init_databases(data &db)
{

    db.add_list_data<sf::Texture>();

    //network.set_protocol(POSITION)
    //network.send<component::position>()
}

/**
 * @brief Main function.
 *
 * @param ac Number of arguments.
 * @param av Arguments.
 * @return int
 * @details The main function is used to manage all the errors possible, set all the preparations (init_databases, parse the config files, etc...)
 * @details and finally launch the game.
 */

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