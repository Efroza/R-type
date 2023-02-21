#include <iostream>
#include <stdexcept>
#include "SFML.hpp"

const std::map<int, events_e> SFML::_confButton {
    {sf::Keyboard::Key::Q,      events_e::CLOSE},
    {sf::Keyboard::Key::Up,     events_e::KEY_UP},
    {sf::Keyboard::Key::Down,   events_e::KEY_DOWN},
    {sf::Keyboard::Key::Left,   events_e::KEY_LEFT},
    {sf::Keyboard::Key::Right,  events_e::KEY_RIGHT},
    {sf::Keyboard::Key::Space,  events_e::SPACE},
    {sf::Keyboard::Key::Escape, events_e::ESCAPE},
    {sf::Keyboard::Key::Enter,  events_e::ENTER},
};

extern "C" IGraphic* createGraphLib()
{
    return (new SFML());
}

SFML::SFML() : AGraphic("SFML")
{
    _window = std::make_shared<sf::RenderWindow>();
}

SFML::~SFML()
{
    _db.clear();
}

void SFML::initialize(int x, int y, const std::string &name)
{
    if (!_window->isOpen()) {
        _window->create(sf::VideoMode(x, y), name);
        _window->setFramerateLimit(60);
    }
}

void SFML::destroy()
{
    if (_window->isOpen()) {
        _window->close();
    }
}

void SFML::clearWindow()
{
    if (_window->isOpen()) {
        _window->clear(sf::Color(sf::Color::Black));
    }
}

void SFML::refreshWindow()
{
    if (_window->isOpen()) {
        _window->display();
    }
}

void SFML::draw(std::shared_ptr<Drawable> image, const std::pair<int, int> &position)
{
    if (_db.find(image->getStr()) == _db.end()) {
        try {
            this->load(image);
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    SMFLObject_t &obj = _db[image->getStr()];
    if (image->isText()) {
        obj.text->setPosition(position.second, position.first);
        obj.text->setString(image->getStr());
        this->_window->draw(*obj.text);
    } else {
        obj.sprite->setTexture(obj.texture);
        obj.sprite->setPosition(position.second, position.first);
        this->_window->draw(*obj.sprite);
    }
}

void SFML::load(std::shared_ptr<Drawable> image)
{
    SMFLObject_t newObject;

    newObject.isText = image->isText();
    if (newObject.isText) {
        newObject.text = std::make_unique<sf::Text>();
        newObject.text->setString(image->getStr());
        newObject.text->setCharacterSize(image->getRect().first);
        newObject.sprite = nullptr;
    } else {
        if (newObject.texture.loadFromFile(image->getStr())) {
            newObject.sprite->setTexture(newObject.texture, true);
            newObject.rect = {0, 0, image->getRect().first, image->getRect().second};
            newObject.sprite->setTextureRect(newObject.rect);
        } else {
            throw std::runtime_error("failed to load texture from: " + image->getStr());
        }
    }
    _db.emplace(image->getStr(), std::move(newObject));
}

events_e SFML::pollEvent()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed) {
            return (CLOSE);
        }
        if (_event.type == sf::Event::KeyPressed) {
            if (_confButton.find(_event.key.code) == _confButton.end()) {
                return NONE;
            }
            return _confButton.at(_event.key.code);
        }
    }
    return NONE;
}