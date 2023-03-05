/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Core
*/


#include <string>
#include <list>
#include "IGraphic.hpp"

enum scene_e {
    HOME,
    NETWORK_MENU,
    GAME
};

class Core
{
public:
    Core();
    ~Core();

    void loop();
private:
    void loadLib(const std::string &filepath);
    void _manageEventMenuHome(events_e event);
    void _manageEventMenuNetwork(events_e event);
    void _manageGameEvent(events_e event);
    
    std::unique_ptr<IGraphic> _libGraphic;
    std::list<std::shared_ptr<Drawable>> _drawables;
    std::list<std::shared_ptr<Drawable>> _homeMenuDrawables;
    std::list<std::shared_ptr<Drawable>> _networkMenuDrawables;
    std::shared_ptr<Drawable> _playBtn;
    std::shared_ptr<Drawable> _exitBtn;
    std::shared_ptr<Drawable> _hostBtn;
    std::shared_ptr<Drawable> _ipBtn;
    std::shared_ptr<Drawable> _lunchBtn;
    std::shared_ptr<Drawable> _background;
    std::string _host;
    std::string _ip;
    scene_e _scene;
    bool _playing;
};