/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Core
*/

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <stdexcept>
#include <functional>
#include <iostream>
#include "Core.hpp"

Core::Core() : _scene(scene_e::HOME), _playing(true), _homeMenuIndex(0)
{
    #ifdef _WIN32
    this->loadLib("./bin/SFML.dll");
    #else
    this->loadLib("lib/libSFML.so");//faut mettre le path de la lib graphique
    #endif

    auto background = std::make_shared<Drawable>("background", "./Engine/Image/background.jpg", std::pair<int, int>(1920, 1080), std::pair<int, int>(0, 0));
    this->_homeMenuDrawables.push_back(background);
    this->_networkMenuDrawables.push_back(background);

    auto rtypeText = std::make_shared<Drawable>("text-rtype", "RTYPE", std::pair<int, int>(200, 200), std::pair<int, int>(650, 100), true, WHITE);
    this->_homeMenuDrawables.push_back(rtypeText);
    this->_networkMenuDrawables.push_back(rtypeText);

    auto firstBtn = std::make_shared<Drawable>("button-first", "./Engine/Image/bouton.png", std::pair<int, int>(300, 104), std::pair<int, int>(810, 500));
    this->_homeMenuDrawables.push_back(firstBtn);
    this->_networkMenuDrawables.push_back(firstBtn);
    auto posFirstBtn = firstBtn->getPosition();

    this->_homeMenuDrawables.push_back(std::make_shared<Drawable>("text-play", "PLAY", std::pair<int, int>(36, 36), std::pair<int, int>(posFirstBtn.first + 100, posFirstBtn.second + 27), true, RED));
    _playBtn = _homeMenuDrawables.back();

    auto secondBtn = std::make_shared<Drawable>("button-second", "./Engine/Image/bouton.png", std::pair<int, int>(300, 104), std::pair<int, int>(810, 700));
    this->_homeMenuDrawables.push_back(secondBtn);
    this->_networkMenuDrawables.push_back(secondBtn);
    auto posSecondBtn = secondBtn->getPosition();

    this->_homeMenuDrawables.push_back(std::make_shared<Drawable>("text-exit", "EXIT", std::pair<int, int>(36, 36), std::pair<int, int>(posSecondBtn.first + 100, posSecondBtn.second + 27), true));
    _exitBtn = _homeMenuDrawables.back();

    // un truc pour tester la scene game
    this->_drawables.push_back(std::make_shared<Drawable>("player", "./Engine/Image/spaceship_jet.png", std::pair<int, int>(200, 176), std::pair<int, int>(200, 200)));

    this->_networkMenuDrawables.push_back(std::make_shared<Drawable>("text-host", "HOST :", std::pair<int, int>(36, 36), std::pair<int, int>(posFirstBtn.first - 140, posFirstBtn.second + 27), true, RED));
    _hostBtn = _networkMenuDrawables.back();

    this->_networkMenuDrawables.push_back(std::make_shared<Drawable>("text-selected-host", "", std::pair<int, int>(36, 36), std::pair<int, int>(posFirstBtn.first + 50, posFirstBtn.second + 27), true));

    this->_networkMenuDrawables.push_back(std::make_shared<Drawable>("text-ip", "IP :", std::pair<int, int>(36, 36), std::pair<int, int>(posSecondBtn.first - 100, posSecondBtn.second + 27), true));
    _ipBtn = _networkMenuDrawables.back();

    this->_networkMenuDrawables.push_back(std::make_shared<Drawable>("text-selected-ip", "", std::pair<int, int>(36, 36), std::pair<int, int>(posSecondBtn.first + 50, posSecondBtn.second + 27), true));

    auto thirdBtn = std::make_shared<Drawable>("button-third", "./Engine/Image/bouton.png", std::pair<int, int>(300, 104), std::pair<int, int>(810, 900));
    this->_networkMenuDrawables.push_back(thirdBtn);
    auto posThirdBtn = thirdBtn->getPosition();

    this->_networkMenuDrawables.push_back(std::make_shared<Drawable>("text-lunch", "PLAY", std::pair<int, int>(36, 36), std::pair<int, int>(posThirdBtn.first + 100, posThirdBtn.second + 27), true));
    _lunchBtn = _networkMenuDrawables.back();
}

Core::~Core()
{
}

void Core::_manageEventMenuHome(events_e event)
{
    if (event == events_e::KEY_DOWN && _homeMenuIndex < 1) {
        _homeMenuIndex += 1;
        _playBtn->setColor(WHITE);
        _exitBtn->setColor(RED);
    } else if (event == events_e::KEY_UP && _homeMenuIndex > 0) {
        _homeMenuIndex -= 1;
        _playBtn->setColor(RED);
        _exitBtn->setColor(WHITE);
    } else if (event == events_e::ENTER) {
        if (_homeMenuIndex == 0) {
            _scene = scene_e::NETWORK_MENU;
        } else if (_homeMenuIndex == 1) {
            _playing = false;
        }
    }
}

void Core::_manageEventMenuNetwork(events_e event)
{
    static int index = 0;
    static bool textMode = false;

    if (event == events_e::ENTER) {
        if (index == 2) {
            _scene = scene_e::GAME;
        } else {
            textMode = !textMode;
        }
    } else if (!textMode) {
        if (event == events_e::KEY_DOWN && index == 0) {
            index += 1;
            _hostBtn->setColor(WHITE);
            _ipBtn->setColor(RED);
        } else if (event == events_e::KEY_UP && index == 1) {
            index -= 1;
            _hostBtn->setColor(RED);
            _ipBtn->setColor(WHITE);
        } else if (event == events_e::KEY_DOWN && index == 1) {
            index += 1;
            _ipBtn->setColor(WHITE);
            _lunchBtn->setColor(RED);
        } else if (event == events_e::KEY_UP && index == 2) {
            index -= 1;
            _lunchBtn->setColor(WHITE);
            _ipBtn->setColor(RED);
        }
    } else {
        if (index == 0) {
            _host = _libGraphic->getText(_host);
        } else if (index == 1) {
            _ip = _libGraphic->getText(_ip);
        }
    }
}

void Core::loop()
{
    events_e event = NONE;

    _libGraphic->initialize(1920, 1080, "Rtype");
    while (_playing) {
        event = _libGraphic->pollEvent();
        if (event == events_e::CLOSE) {
            _playing = false;
        } else if (event == events_e::ENTER) {
            std::cout << "ENTER\n";
        } else if (event == events_e::KEY_LEFT) {
            std::cout << "KEY_LEFT\n";
        } else if (event == events_e::KEY_RIGHT) {
            std::cout << "KEY_RIGHT\n";
        } else if (event == events_e::ESCAPE) {
            std::cout << "ESCAPE\n";
            _playing = false;
        } else if (event == events_e::KEY_DOWN) {
            std::cout << "KEY_DOWN\n";
        } else if (event == events_e::KEY_UP) {
            std::cout << "KEY_UP\n";
        }
        _libGraphic->clearWindow();
        switch (_scene) {
        case scene_e::HOME:
            _manageEventMenuHome(event);
            for (auto &i : _homeMenuDrawables) {
                _libGraphic->draw(i, i->getPosition());
            }
            break;
        case scene_e::NETWORK_MENU:
            _manageEventMenuNetwork(event);
            for (auto &i : _networkMenuDrawables) {
                if (i->getName() == "text-selected-host") {
                    i->setStr(_host);
                } else if (i->getName() == "text-selected-ip") {
                    i->setStr(_ip);
                }
                _libGraphic->draw(i, i->getPosition());
            }
            break;
        case scene_e::GAME:
            std::cout << "afficher le jeu" << std::endl;
            for (auto &i : _drawables) {
                if (i->getName() == "player") {
                    auto j = i->getPosition();
                    i->setPosition({j.first, j.second - 1});
                }
            _libGraphic->draw(i, i->getPosition());
            }
            break;
        default:
            break;
        }
        _libGraphic->refreshWindow();
    }
    _libGraphic->destroy();
}

void Core::loadLib(const std::string &filepath)
{
    #ifdef _WIN32 // Windows
    // std::cout << filepath << std::endl;
    HINSTANCE handle = LoadLibrary(filepath.c_str());
    if (!handle) {
        throw std::runtime_error("Error Load Library: " + std::to_string(GetLastError()));
    }
    IGraphic *(*funcPtr)() = reinterpret_cast<IGraphic *(*)()>(GetProcAddress(handle, "createGraphLib"));
    if (!funcPtr) {
        throw std::invalid_argument(std::string("Invalid lib: ") + std::to_string(GetLastError()));
    }
    #else // Linux
    void *handle = dlopen(filepath.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("Error dlopen: " + std::string(dlerror()));
    }
    IGraphic *(*funcPtr)() = reinterpret_cast<IGraphic *(*)()>(dlsym(handle, "createGraphLib"));
    if (!funcPtr) {
        throw std::invalid_argument(std::string("Invalid lib: ") + dlerror());
    }
    #endif

    auto a = std::function<IGraphic * ()>(funcPtr);
    _libGraphic.reset(std::move(a()));
    if (_libGraphic.get() == nullptr) {
        throw std::runtime_error("Error during lib loading");
    }

}
