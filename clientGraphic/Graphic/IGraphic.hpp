/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** IGraphic
*/

#ifndef IGRAPHIC_HPP
#define IGRAPHIC_HPP

#include <memory>
#include "../Drawable/Drawable.hpp"
#include "events.hpp"

class IGraphic
{
public:
    virtual ~IGraphic() = default;

    virtual const std::string &getName() const = 0;
    virtual void initialize(int x, int y, const std::string &name) = 0;
    virtual void destroy() = 0;
    virtual void clearWindow() = 0;
    virtual void refreshWindow() = 0;
    virtual void draw(std::shared_ptr<Drawable> image, const std::pair<int, int> &position) = 0;
    virtual events_e pollEvent() = 0;
};

extern "C" IGraphic* createGraphLib();

#endif