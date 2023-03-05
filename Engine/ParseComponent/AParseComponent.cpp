/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** AParseComponent
*/

#include "AParseComponent.hpp"

/**
 * @file AParseComponent.cpp
 *
 * @brief This file contains the implementation of the AParseComponent class
 */

/**
 * @brief Construct a new AParseComponent::AParseComponent object
 *
 * @param name name of the component
 */

AParseComponent::AParseComponent(std::string const &name)
: _name(name)
{
}

AParseComponent::~AParseComponent()
{
}

/**
 * @brief Get the name object
 *
 * @return std::string
 */

std::string &AParseComponent::get_name() noexcept
{
    return _name;
}

/**
 * @brief Get the number arguments needed object
 *
 * @return std::uint8_t
 */

std::uint8_t AParseComponent::number_arguments_needed() const noexcept
{
    return _args.size();
}

/**
 * @brief This function return all the arguments fo the component in a map
 *
 * @return IParseComponent::parse_map
 */

IParseComponent::parse_map AParseComponent::get_arguments() noexcept
{
    return _args;
}

/**
 * @brief This function return the arguments needed by the component in a const map
 *
 * @return IParseComponent::parse_map const &
 */

IParseComponent::parse_map const &AParseComponent::argument_needed() noexcept
{
    return _args;
}

/**
 * @brief Set the argument needed object
 *
 * @param json json object
 * @param key key of the argument
 * @return true if the argument is set correctly and false otherwise
 */

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