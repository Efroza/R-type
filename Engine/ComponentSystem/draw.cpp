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

/**
 * @file draw.cpp
 */

componentSystem::draw::draw()
{
}

componentSystem::draw::~draw()
{
}

/**
 * @brief Factory function for creating an instance of the draw component system.
 *
 * @return A pointer to a new instance of the draw component system.
 * @details The function is declared as extern "C", which specifies that it has C linkage (i.e., it can be called from C code).
 * @details This is necessary because the component system is loaded as a shared library.
 */
extern "C" IComponentSystem *createComponentSystem()
{
    return new componentSystem::draw;
}

/**
 * @brief Will load the texture into the data object and associate it with the given id if it is not already loaded.
 *
 * @param id The id of the texture.
 * @param db Represent the data object for storing the image data.
 * @param file The file path of the image.
 */
static void load_texture(std::uint8_t id, data *db, const std::string &file)
{
    sf::Texture texture;
    if (!texture.loadFromFile(file))
        throw std::runtime_error("error load file " + file + " into texture");
    texture.setSmooth(true);
    db->insert_data<sf::Texture>(std::move(texture), id);
}

/**
 * @brief Updates the draw component system by processing all relevant image, position, and rectangle components.
 *
 * @param reg The registry containing all entities and their associated components.
 * @param images The sparse array of image components.
 * @param positions The sparse array of position components.
 * @param rects The sparse array of rectangle components.
 * @param interactions The sparse array of interaction components.
 * @param db Represent the data object for storing the image data.
 * @param window The window in which the image will be drawn.
 * @details The function will draw all images in the window.
 */
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

/**
 * @brief Will manage the event of the window like (close, key pressed, mouse pressed, etc...)
 *
 * @param event SFML variable for managing all event from the window
 * @param window Where the event will be managed (SFML), where the image will be drawn
 * @param interactions The sparse array of interaction components like (up, down, left, right, etc...)
 */
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

/**
 * @brief Draws images on the screen according to their positions and draw properties.
 *
 * @param reg The registry containing all entities and their associated components.
 * @param images The sparse array of image components to draw.
 * @param positions The sparse array of position components associated with the images.
 * @param draw The sparse array of draw components associated with the images.
 */
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

/**
 * @brief Create a rect object
 *
 * @param id Record the id of the rect object to recover it later
 * @param db Where the rect will be stored
 * @param rect Component that will help to create the rect object in SFML
 */
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

/**
 * @brief Update the rect object
 *
 * @param id Record the id of the rect object to recover it later
 * @param db Where the rect will be stored
 * @param rect Component that will help to update the rect object in SFML
 * @details The function will update the rect object in SFML, to check is state and update it.
 */
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

/**
 * @brief Load the rect object
 *
 * @param id Record the id of the rect object to recover it later
 * @param db Where the rect is stored
 * @param rect Component that will help to load the rect object in SFML
 * @details The function will load the rect object in SFML.
 */
static void load_rect(std::uint32_t id, data *db, component::rect &rect)
{
    if (db == nullptr || db->data_exist<sf::Sprite>(id) == false || db->data_exist<sf::IntRect>(id) == false)
        return;
    sf::Sprite &sprite = db->get_data<sf::Sprite>(id);
    sf::IntRect &rect_sfml = db->get_data<sf::IntRect>(id);
    sprite.setTextureRect(rect_sfml);
}

/**
  * @brief System responsible for updating and drawing rectangular shapes.
  *
  * @param reg A reference to the entity-component system registry.
  * @param rects A sparse array of components that contain the rectangular shape properties for each entity.
  * @param images A sparse array of components that contain the image properties for each entity.
  * @param draw A sparse array of components that determine whether an entity should be drawn.
  * @details This system iterates through the sparse arrays of components (images, rects, and draw)
  * @details and for each entity with all three components, it checks if the image has a valid
  * @details database pointer. If so, it checks if the entity has a valid sf::IntRect object in
  * @details the database. If not, it creates one, otherwise it updates and loads the existing one.
  */
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