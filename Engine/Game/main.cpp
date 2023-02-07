/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** main
*/

#include <SFML/Window.hpp>
#include "systems.hpp"
#include "draw.hpp"

void create_spaceShip(registry &reg, data &db)
{
    entity_t spaceship = reg.spawn_entity();
    try {
        reg.add_component<component::position>(spaceship, std::move(component::position(100, 100)));
        reg.add_component<component::image>(spaceship, std::move(component::image("Image/spaceship.png", db, spaceship)));
        reg.add_component<component::draw>(spaceship, std::move(component::draw()));
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void game(registry &reg)
{
    data db;
    sf::RenderWindow &window = reg.get_window();
    sf::Event event;

    load_system(reg);
    load_component(reg);
    create_spaceShip(reg, db);
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        reg.run_systems();
        window.display();
    }
}

int main(void)
{
    registry reg(sf::VideoMode(800, 600), "Rtype");
    add_entity(component::position(5, 5), 1);
    add_entity(component::position(10, 10), 1);
    game(reg);
    return 0;
}