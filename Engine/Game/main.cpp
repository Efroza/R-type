/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** main
*/

#include <unistd.h>
#include <SFML/Window.hpp>
#include "draw.hpp"
#include "handle_entity.hpp"
#include "rect.hpp"
#include "systems.hpp"
#include "interaction.hpp"
#include "interactive.hpp"
#include "handling_interaction.hpp"

void handle_config_files(std::vector<std::string> const &files, registry &reg, data &db, handling_interaction &interaction);

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

void game(registry &reg, data &db)
{
    sf::RenderWindow &window = reg.get_window();
    sf::Event event;
    handle_entity handle(reg, db);

    load_system(reg);
    load_component(reg);
    std::vector<std::string> config = {"./Config/other.json", "./Config/spaceship.json"};
    std::vector<std::string> interaction_config = {"./Interaction/up_deplacement.so", "./Interaction/down_deplacement.so", "./Interaction/left_deplacement.so", "./Interaction/right_deplacement.so"};
    handling_interaction interaction(interaction_config);
    handle_config_files(config, reg, db, interaction);
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        usleep(2000);
        reg.run_systems();
        window.display();
    }
}

void init_databases(data &db)
{

    db.add_list_data<sf::Texture>();
}

int main(void)
{
    registry reg(sf::VideoMode(800, 600), "Rtype");
    data db;

    init_databases(db);
    game(reg, db);
    return 0;
}