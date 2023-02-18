/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** AParseComponent
*/

#ifndef APARSECOMPONENT_HPP_
#define APARSECOMPONENT_HPP_

#include "IParseComponent.hpp"

class AParseComponent : public IParseComponent {
    public:
        AParseComponent(std::string const &name = "");
        ~AParseComponent();
        std::string &get_name() noexcept;
        std::uint8_t number_arguments_needed() const noexcept;
        parse_map get_arguments() noexcept;
        parse_map const &argument_needed() noexcept;
        template <class type>
        void set_argument_needed(std::string const &name) {
            _args[name] = typeid(type).hash_code();
        }
        bool good_arg(Json::Value const &json, std::string const &key) const noexcept;
        virtual void load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const = 0;

    protected:
        std::string _name;
        parse_map _args;

    private:
};

#endif /* !APARSECOMPONENT_HPP_ */