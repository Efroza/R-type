/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** IParseComponent
*/

#ifndef IPARSECOMPONENT_HPP_
#define IPARSECOMPONENT_HPP_

#include <vector>
#include <cinttypes>
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <json/json.h>
#include <json/value.h>
#include <unordered_map>
#include "../Include/data.hpp"
#include "../Include/entity.hpp"
#include "../Include/registry.hpp"

class IParseComponent {
    public:
        using parse_map = std::unordered_map<std::string, std::uint64_t>;

    public:
        ~IParseComponent() = default;
        virtual std::string &get_name() noexcept = 0;
        virtual std::uint8_t number_arguments_needed() const noexcept = 0;
        virtual parse_map get_arguments() noexcept = 0;
        virtual parse_map const &argument_needed() noexcept = 0;
        // virtual void set_argument_needed(std::string const &name, std::type_index const &type) = 0;
        virtual bool good_arg(Json::Value const &json, std::string const &key) const noexcept = 0;
        virtual void load_component(entity_t const &e, registry &reg, data &db, Json::Value const &json) const = 0;

    protected:
    private:
};

#endif /* !IPARSECOMPONENT_HPP_ */
