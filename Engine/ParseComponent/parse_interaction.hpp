/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** parse_interaction
*/

#ifndef PARSE_INTERACTION_HPP_
#define PARSE_INTERACTION_HPP_

#include "AParseComponent.hpp"
#include "AParseInteraction.hpp"

namespace parse_component
{
    class interaction : public AParseComponent, public AParseInteraction
    {
        public:
            interaction();
            ~interaction();
            void handling_string_interaction(entity_t const &e, registry &reg, std::string const &key, std::string const &interaction_name) const noexcept;
            void load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const;
    };
};

#endif /* !PARSE_INTERACTION_HPP_ */