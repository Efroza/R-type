/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** main
*/

#include <SFML/Window.hpp>
#include <unistd.h>
#include "systems.hpp"
#include "draw.hpp"
#include "handle_entity.hpp"
#include "rect.hpp"
#include "interaction.hpp"
#include "interactive.hpp"

void handle_config_files(std::vector<std::string> const &files, registry &reg, data &db);

void create_spaceShip(registry &reg, data &db)
{
    entity_t spaceship = reg.spawn_entity();
    component::interaction inter;

    inter.new_interaction(sf::Keyboard::Space, up_deplacement);

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

void game(registry &reg)
{
    data db;
    sf::RenderWindow &window = reg.get_window();
    sf::Event event;
    handle_entity handle(reg, db);

    load_system(reg);
    load_component(reg);
    // create_spaceShip(reg, db);
    // handle.create_entity(component::position(100, 100), reg.spawn_entity());
    std::vector<std::string> config = {"./Config/spaceship.json"};
    handle_config_files(config, reg, db);
    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        usleep(2000);
        reg.run_systems();
        window.display();
    }
}

int main(void)
{
    registry reg(sf::VideoMode(800, 600), "Rtype");
    game(reg);
    return 0;
}