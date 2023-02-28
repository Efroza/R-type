/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_network
*/

#ifndef PARSE_NETWORK_HPP_
#define PARSE_NETWORK_HPP_

#include "AParseComponent.hpp"

namespace parse_component
{
    class network : public AParseComponent
    {
    public:
        network();
        ~network();
        void load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const;
    };
};

#endif /* !PARSE_NETWORK_HPP_ */
