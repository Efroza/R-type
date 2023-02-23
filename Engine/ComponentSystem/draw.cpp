/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** draw
*/

#include "draw.hpp"
#include "image.hpp"
#include "position.hpp"
#include <SFML/Graphics.hpp>

componentSystem::draw::draw()
{
}

componentSystem::draw::~draw()
{
}

extern "C" IComponentSystem *createComponentSystem()
{
    return new componentSystem::draw;
}

static void load_texture(std::uint8_t id, data *db, const std::string &file)
{
    sf::Texture texture;
    if (!texture.loadFromFile(file))
        throw std::runtime_error("error load file " + file + " into texture");
    texture.setSmooth(true);
    db->insert_data<sf::Texture>(std::move(texture), id);
}

static void create_sprite(std::uint8_t id, data *db, component::image &image, component::position &position)
{
    if (db->data_exist<sf::Sprite>(id) == true)
        return;
    if (db->type_exist<sf::Sprite>() == false)
        db->add_list_data<sf::Sprite>();

    sf::Sprite sprite;
    load_texture(id, db, image.name_file);
    sf::Texture &texture = db->get_data<sf::Texture>(id);
    sprite.setTexture(texture);
    db->insert_data<sf::Sprite>(std::move(sprite), id);
    std::cout << "texture added: " << image.name_file << std::endl;
}

static void handle_event(sf::Event &event, sf::RenderWindow &window)
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
    }
}

void draw_system(registry &reg
, sparse_array<component::image> &images
, sparse_array<component::position> &positions
, sparse_array<component::draw> &draw)
{
    if (draw.size() == 0)
        return;
    static sf::RenderWindow window(sf::VideoMode(800, 600), "Rtype");
    data *db = nullptr;
    sf::Event event;

    if (window.isOpen() == false) {
        window.~RenderWindow();
        return;
    }
    window.clear(sf::Color::Black);
    handle_event(event, window);
    for (std::uint32_t i = 0; i < images.size() && i < positions.size() && i < draw.size(); ++i) {
        if (!images[i] || !positions[i] || !draw[i])
            continue;
        db = images[i].value().db;
        if (db == nullptr)
            continue;
        try {
            create_sprite(i, db, images[i].value(), positions[i].value());
        } catch (std::exception const &e) {
            std::cerr << e.what() << std::endl;
            reg.remove_component<component::draw>(i);
            continue;
        }
        sf::Sprite &sprite = db->get_data<sf::Sprite>(i);
        sprite.setPosition(positions[i].value().x, positions[i].value().y);
        window.draw(sprite);
        window.display();
    }
}

std::string componentSystem::draw::get_name() const noexcept
{
    return "draw";
}

void componentSystem::draw::laod_component(registry &reg) const noexcept
{
    reg.register_component<component::draw>();
}

void componentSystem::draw::load_system(registry &reg) const noexcept
{
    reg.add_system<component::image, component::position, component::draw>(draw_system);
}

void componentSystem::draw::add_entity_component(registry &reg, entity_t &e) const noexcept
{
    reg.add_component<component::draw>(e, std::move(component::draw()));
}