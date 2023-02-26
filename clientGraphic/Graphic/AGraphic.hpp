/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** AGraphic
*/



#ifndef AGRAPHIC_HPP
#define AGRAPHIC_HPP

#include "IGraphic.hpp"

class AGraphic : public IGraphic
{
public:
    AGraphic(const std::string &name);
    virtual ~AGraphic() = default;

    const std::string &getName() const final;
protected:
    std::string _graphLib;
};

#endif