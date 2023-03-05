/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** IComponents
*/


#ifndef ICOMPONENT_HPP

#include "ComponentType.hpp"

class IComponents
{
public:
    virtual ~IComponents() = default;
    virtual ComponentType const &getType() const = 0;
    virtual void setType(ComponentType& type) = 0;
private:
    /* data */
};


#endif