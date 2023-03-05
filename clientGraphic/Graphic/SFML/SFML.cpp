/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** SFML
*/


#include <iostream>
#include <stdexcept>
#include "SFML.hpp"

const std::map<int, events_e> SFML::_confInputs {
    // {sf::Keyboard::Key::Q,      events_e::CLOSE}, // press q = CLOSE event => close window
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
    _confColors.emplace(colors_e::NO_COLOR, sf::Color::Transparent);
    _confColors.emplace(colors_e::WHITE,    sf::Color::White);
    _confColors.emplace(colors_e::BLACK,    sf::Color::Black);
    _confColors.emplace(colors_e::RED,      sf::Color::Red);
    _confColors.emplace(colors_e::GREEN,    sf::Color::Green);
    _confColors.emplace(colors_e::BLUE,     sf::Color::Blue);
    _confColors.emplace(colors_e::CYAN,     sf::Color::Cyan);
    _confColors.emplace(colors_e::MAGENTA,  sf::Color::Magenta);
    _confColors.emplace(colors_e::YELLOW,   sf::Color::Yellow);
    _confNumberInput.emplace(sf::Keyboard::Key::Num0, '0');
    _confNumberInput.emplace(sf::Keyboard::Key::Num1, '1');
    _confNumberInput.emplace(sf::Keyboard::Key::Num2, '2');
    _confNumberInput.emplace(sf::Keyboard::Key::Num3, '3');
    _confNumberInput.emplace(sf::Keyboard::Key::Num4, '4');
    _confNumberInput.emplace(sf::Keyboard::Key::Quote, '4');
    _confNumberInput.emplace(sf::Keyboard::Key::Num5, '5');
    _confNumberInput.emplace(sf::Keyboard::Key::Num6, '6');
    _confNumberInput.emplace(sf::Keyboard::Key::Hyphen, '6');
    _confNumberInput.emplace(sf::Keyboard::Key::Num7, '7');
    _confNumberInput.emplace(sf::Keyboard::Key::Num8, '8');
    _confNumberInput.emplace(sf::Keyboard::Key::Num9, '9');
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
    if (!_font.loadFromFile("Engine/Image/8bitsFont.ttf")) {
        std::cerr << "Font not found" << std::endl;
        return;
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
            std::cout << "try to load: " << image->getStr() << std::endl;
            this->load(image);
            std::cout << "load succed: " << image->getStr() << std::endl;
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
    SMFLObject_t &obj = _db[image->getStr()];
    if (image->isText()) {
        obj.text->setPosition(position.first, position.second);
        obj.text->setString(image->getStr());
        obj.text->setFillColor(_confColors.at(image->getColor()));
        this->_window->draw(*obj.text);
    } else {
        obj.sprite->setTexture(obj.texture);
        obj.sprite->setPosition(position.first, position.second);
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
        newObject.text->setFont(_font);
        newObject.text->setCharacterSize(image->getRect().first);
        newObject.text->setFillColor(_confColors.at(image->getColor()));
        newObject.sprite = nullptr;
    } else {
        newObject.sprite = std::make_unique<sf::Sprite>();
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
            if (_confInputs.find(_event.key.code) == _confInputs.end()) {
                return events_e::NONE;
            }
            return _confInputs.at(_event.key.code);
        }
    }
    return events_e::NONE;
}

std::string SFML::getText(std::string str)
{
    if (_event.type == sf::Event::KeyPressed) {
        if (_event.key.code == sf::Keyboard::BackSpace && !str.empty()) {
            str.pop_back();
        } else if (_event.text.unicode < 26)
            str += (_event.text.unicode + 'a');
        else if (_confNumberInput.find(_event.key.code) != _confNumberInput.end()) {
            std::cout << "INPUT: " << _event.text.unicode << std::endl;
            str += (_confNumberInput.at(_event.key.code));
        }
    std::cout << "INPUT: " << _event.text.unicode << std::endl;
    }
    return (str);
}
