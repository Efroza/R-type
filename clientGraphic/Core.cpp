/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Core
*/

#include <dlfcn.h>
#include <stdexcept>
#include <functional>
#include <iostream>
#include "Core.hpp"

Core::Core(Client &init_client) : client(&init_client)
{
    this->loadLib("lib/libSFML.so");//faut mettre le path de la lib graphique
    this->_drawables.push_back(std::make_shared<Drawable>("./Engine/Image/spaceship_jet.png", std::pair<int, int>(400, 400)));
}

Core::~Core()
{
}

void Core::loop()
{
    events_e event = NONE;

    _libGraphic->initialize(800, 600, "Rtype");
    while (true) {
        event = _libGraphic->pollEvent();
        if (event == events_e::CLOSE) {
            break;
        } else if (event == events_e::ENTER) {
            std::cout << "ENTER\n";
        } else if (event == events_e::KEY_LEFT) {
            std::cout << "KEY_LEFT\n";
        } else if (event == events_e::KEY_RIGHT) {
            std::cout << "KEY_RIGHT\n";
        } else if (event == events_e::ESCAPE) {
            std::cout << "ESCAPE\n";
        } else if (event == events_e::KEY_DOWN) {
            std::cout << "KEY_DOWN\n";
        } else if (event == events_e::KEY_UP) {
            std::cout << "KEY_UP\n";
        }
        _libGraphic->clearWindow();
        _libGraphic->draw(_drawables.front(), {10, 10});
        _libGraphic->refreshWindow();
    }
    _libGraphic->destroy();
}

void Core::loadLib(const std::string &filepath)
{
    void *handle = dlopen(filepath.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("Error dlopen: " + std::string(dlerror()));
    }
    IGraphic *(*funcPtr)() = (IGraphic *(*)())dlsym(handle, "createGraphLib");
    if (!funcPtr) {
        throw std::invalid_argument(std::string("Invalid lib: ") + dlerror());
    }
    auto a = std::function<IGraphic * ()>(funcPtr);
    _libGraphic.reset(std::move(a()));
    if (_libGraphic.get() == nullptr) {
        throw std::runtime_error("Error during lib loading");
    }
}
