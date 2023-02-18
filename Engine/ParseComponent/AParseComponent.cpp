/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** AParseComponent
*/

#include "AParseComponent.hpp"

AParseComponent::AParseComponent(std::string const &name)
: _name(name)
{
}

AParseComponent::~AParseComponent()
{
}

std::string &AParseComponent::get_name() noexcept
{
    return _name;
}

std::uint8_t AParseComponent::number_arguments_needed() const noexcept
{
    return _args.size();
}

IParseComponent::parse_map AParseComponent::get_arguments() noexcept
{
    return _args;
}

IParseComponent::parse_map const &AParseComponent::argument_needed() noexcept
{
    return _args;
}

bool AParseComponent::good_arg(Json::Value const &json, std::string const &key) const noexcept
{
    if (json[key].empty())
        return false;
    if (_args.find(key) == _args.end())
        return false;
    if (_args.at(key) == std::type_index(typeid(int)).hash_code())
        return json[key].isInt();
    if (_args.at(key) == std::type_index(typeid(std::uint8_t)).hash_code())
        return json[key].isUInt();
    if (_args.at(key) == std::type_index(typeid(std::uint64_t)).hash_code())
        return json[key].isUInt64();
    if (_args.at(key) == std::type_index(typeid(double)).hash_code())
        return json[key].isDouble();
    if (_args.at(key) == std::type_index(typeid(std::string)).hash_code())
        return json[key].isString();
    return false;
}