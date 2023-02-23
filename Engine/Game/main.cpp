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
#include "handle_entity.hpp"
#include "rect.hpp"
#include "systems.hpp"
#include "interaction.hpp"
#include "interactive.hpp"
#include "handling_interaction.hpp"
#include "Yaml.hpp"

void create_spaceShip(registry &reg, data &db)
{
    entity_t spaceship = reg.spawn_entity();
    component::interaction inter;

    inter.new_interaction(sf::Keyboard::Space, up_deplacement_function);

    try {
        reg.add_component<component::position>(spaceship, std::move(component::position(100, 100)));
        reg.add_component<component::image>(spaceship, std::move(component::image("Image/spaceship.png", db, spaceship)));
        reg.add_component<component::interaction>(spaceship, std::move(inter));
        reg.add_component<component::rect>(spaceship, std::move(component::rect(1, 6)));
        reg.add_component<component::animation>(spaceship, std::move(component::animation(50)));
        reg.add_component<component::draw>(spaceship, std::move(component::draw()));
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void game(registry &reg, data &db, Yaml &yaml)
{
    sf::RenderWindow &window = reg.get_window();
    sf::Event event;
    handle_entity handle(reg, db);

    load_system(reg);
    load_component(reg);
    std::vector<std::string> config = yaml.get("config_json");
    std::vector<std::string> interaction_config = yaml.get("config_interaction");
    handling_component_system cs_lib = yaml.get("config_component_system");
    handling_interaction interaction(interaction_config);
    parsing handling_parse(reg, db, config);
    handling_parse.handle_config_files(interaction, cs_lib);
    window.close();
    while (true)
        reg.run_systems();
    // while (window.isOpen())
    // {
    //     window.clear(sf::Color::Black);
    //     usleep(2000);
    //     reg.run_systems();
    //     window.display();
    // }
}

void init_databases(data &db)
{

    db.add_list_data<sf::Texture>();
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
        registry reg(sf::VideoMode(800, 600), "Rtype");
        init_databases(db);
        game(reg, db, yaml);
    } catch(std::exception const &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
}
    // void *handle = dlopen("../lib/libSFML.so", RTLD_LAZY);
    // if (!handle) {
    //     std::cout << "Error dl open " << dlerror() << std::endl;
    //     return 84;
    // }
    // IGraphic *(*funcPtr)() = (IGraphic *(*)())dlsym(handle, "createGraphLib");
    // if (!funcPtr) {
    //     throw std::invalid_argument(std::string("Invalid lib: ") + dlerror());
    // }
    // auto a = std::function<IGraphic * ()>(funcPtr);
    // std::unique_ptr<IGraphic> libgraph(std::move(a()));
    // libgraph->initialize(800, 600, "Rtype");
    // while (true) {
    //     if (libgraph->pollEvent() == CLOSE) {
    //         break;
    //     }
    // }
    // libgraph->destroy();
    // // registry reg(sf::VideoMode(800, 600), "Rtype");
    // // game(reg);