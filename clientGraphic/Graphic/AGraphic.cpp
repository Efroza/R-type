#include "AGraphic.hpp"

AGraphic::AGraphic(const std::string &name) : _graphLib(name)
{
}

const std::string &AGraphic::getName() const
{
    return this->_graphLib;
}