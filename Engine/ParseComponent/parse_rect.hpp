/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_rect
*/

#ifndef PARSE_RECT_HPP_
#define PARSE_RECT_HPP_

#include "AParseComponent.hpp"

namespace parse_component
{
    class rect : public AParseComponent
    {
    public:
        rect();
        ~rect();
        void load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const;
    };
};

#endif /* !PARSE_RECT_HPP_ */
