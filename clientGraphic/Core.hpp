/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Core
*/


#include <string>
#include <list>
#include "IGraphic.hpp"
#include "./include/client.hpp"

class Core
{
public:
    Core(Client &init_client);
    ~Core();

    void loop();
private:
    void loadLib(const std::string &filepath);
    
    std::unique_ptr<IGraphic> _libGraphic;
    std::list<std::shared_ptr<Drawable>> _drawables;
    Client *client;
};