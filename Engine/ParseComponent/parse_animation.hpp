/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_animation
*/

#ifndef PARSE_ANIMATION_HPP_
#define PARSE_ANIMATION_HPP_
#include "AParseComponent.hpp"

namespace parse_component
{
    class animation : public AParseComponent
    {
    public:
        animation();
        ~animation();
        void load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const;
    };
};

#endif /* !PARSE_ANIMATION_HPP_ */
