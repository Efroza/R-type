/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_position
*/

#ifndef PARSE_POSITION_HPP_
#define PARSE_POSITION_HPP_

#include "AParseComponent.hpp"

namespace parse_component {
    class position : public AParseComponent{
        public:
            position();
            ~position();
            void load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const;
    };
};

#endif /* !PARSE_POSITION_HPP_ */