/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_draw
*/

#ifndef PARSE_DRAW_HPP_
#define PARSE_DRAW_HPP_

#include "AParseComponent.hpp"

namespace parse_component
{
    class draw : public AParseComponent
    {
        public:
            draw();
            ~draw();
            void load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const;
    };
};

#endif /* !PARSE_DRAW_HPP_ */
