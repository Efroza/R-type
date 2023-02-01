/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** main
*/

#include <SFML/Window.hpp>
#include "systems.hpp"

void create_spaceShip(registry &reg)
{
    entity_t spaceship = reg.spawn_entity();
    try {
        reg.add_component<component::position>(spaceship, std::move(component::position(100, 100)));
        reg.add_component<component::image>(spaceship, std::move(component::image("Image/spaceship.png")));
        reg.add_component<component::draw>(spaceship, std::move(component::draw()));
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

// void load_component(registry &reg)
// {
//     reg.register_component<component::image>();
//     reg.register_component<component::position>();
//     reg.register_component<component::draw>();
// }

// void register_system(registry &reg)
// {
//     reg.add_system<component::position, component::image>(position_system);
//     reg.add_system<component::draw, component::image>(draw_system);
// }

void game(registry &reg)
{
    //
    sf::Texture texture;
    texture.loadFromFile("Image/spaceship.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(80, 90);
    //
    sf::RenderWindow &window = reg.get_window();
    sf::Event event;

    load_system(reg);
    load_component(reg);
    create_spaceShip(reg);
    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // window.draw(sprite);
        reg.run_systems();
        window.display();
    }
}

int main(void)
{
    registry reg(sf::VideoMode(800, 600), "Rtype");
    game(reg);
    // sf::RenderWindow &window = reg.get_window();

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }
    // }

    return 0;
}