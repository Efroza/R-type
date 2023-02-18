/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_image
*/

#ifndef PARSE_IMAGE_HPP_
#define PARSE_IMAGE_HPP_

#include "AParseComponent.hpp"

namespace parse_component
{
    class image : public AParseComponent
    {
        public:
            image();
            ~image();
            void load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const;
    };
};

#endif /* !PARSE_IMAGE_HPP_ */