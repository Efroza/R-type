/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** AComponent
*/


#ifndef ACOMPONENT_HPP

#include "IComponents.hpp"

class AComponent : public IComponents
{
public:
    AComponent(ComponentType type);
    virtual ~AComponent() = default;
    void setType(ComponentType& type) final;
    ComponentType const &getType() const final;
private:
    ComponentType _type;
};


#endif