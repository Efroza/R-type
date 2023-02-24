/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** draw
*/

#include "draw.hpp"
#include "image.hpp"
#include "position.hpp"
#include "interaction.hpp"
#include "rect.hpp"
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

static void handle_event(sf::Event &event, sf::RenderWindow &window, sparse_array<component::interaction> &interactions)
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
        if (event.type == sf::Event::KeyPressed) {
            for (size_t i = 0; i < interactions.size(); ++i)
                if (interactions[i])
                    interactions[i].value().typing.emplace_back(event.key.code);
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
    sparse_array<component::interaction> &interactions = reg.get_components<component::interaction>();
    data *db = nullptr;
    sf::Event event;

    if (window.isOpen() == false) {
        window.~RenderWindow();
        return;
    }
    window.clear(sf::Color::Black);
    handle_event(event, window, interactions);
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

static void create_rect(std::uint32_t id, data *db, component::rect &rect)
{
    if (db == nullptr || db->data_exist<sf::Texture>(id) == false)
        return;
    sf::Texture &texture = db->get_data<sf::Texture>(id);
    sf::IntRect rect_sfml;
    rect.set_size(texture.getSize().x, texture.getSize().y);
    rect.update();
    rect_sfml.top = rect.top;
    rect_sfml.left = rect.left;
    rect_sfml.width = rect.width;
    rect_sfml.height = rect.height;
    if (db->type_exist<sf::IntRect>() == false)
        db->add_list_data<sf::IntRect>();
    db->insert_data<sf::IntRect>(std::move(rect_sfml), id);
}

static void update_rect(std::uint32_t id, data *db, component::rect &rect)
{
    if (db == nullptr || db->data_exist<sf::IntRect>(id) == false)
        return;
    sf::IntRect &rect_sfml = db->get_data<sf::IntRect>(id);
    rect_sfml.top = rect.top;
    rect_sfml.left = rect.left;
    rect_sfml.width = rect.width;
    rect_sfml.height = rect.height;
}

static void load_rect(std::uint32_t id, data *db, component::rect &rect)
{
    if (db == nullptr || db->data_exist<sf::Sprite>(id) == false || db->data_exist<sf::IntRect>(id) == false)
        return;
    sf::Sprite &sprite = db->get_data<sf::Sprite>(id);
    sf::IntRect &rect_sfml = db->get_data<sf::IntRect>(id);
    sprite.setTextureRect(rect_sfml);
}

void draw_rect_system(registry &reg
, sparse_array<component::rect> &rects
, sparse_array<component::image> &images
, sparse_array<component::draw> &draw)
{
    data *db = nullptr;

    for (std::uint32_t i = 0; i < images.size() && i < rects.size() && i < draw.size(); ++i) {
        if (!images[i] || !rects[i] || !draw[i])
            continue;
        db = images[i].value().db;
        try {
            if (db->data_exist<sf::IntRect>(i) == false)
                create_rect(i, db, rects[i].value());
            update_rect(i, db, rects[i].value());
            load_rect(i, db, rects[i].value());
        } catch (std::exception const &e) {
            std::cout << e.what() << std::endl;
        }
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
    reg.add_system<component::rect, component::image, component::draw>(draw_rect_system);
}

void componentSystem::draw::add_entity_component(registry &reg, entity_t &e) const noexcept
{
    reg.add_component<component::draw>(e, std::move(component::draw()));
}