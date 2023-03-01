/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Yaml
*/

#include "Yaml.hpp"

/**
 * @file Yaml.cpp
 */

/**
 * @brief Construct a new Yaml:: Yaml object
 *
 * @param _fileConf Name of the YAML file to parse.
 */

Yaml::Yaml(std::string const &_fileConf)
{
    if (_fileConf.empty() || !std::ifstream(_fileConf))
        throw std::runtime_error("No config file or config file not found");
    _config = YAML::LoadFile(_fileConf);
    if (_config.IsNull())
        throw std::runtime_error("Config file is empty or invalid");
}

Yaml::~Yaml()
{
}

/**
 * @brief Get the data from the YAML file.
 *
 * @param info Name of the data to get.
 * @return std::string Data.
 */

std::vector<std::string> Yaml::get(std::string const &info) const
{
    try {
        return _config[info].as<std::vector<std::string>>();
    } catch (const std::exception &e) {
        throw std::runtime_error("Can't get this info from that config file");
    }
}

/**
 * @brief Check if the data exist in the YAML file.
 *
 * @param key Name of the data to check.
 * @return true If the data exist.
 * @return false If the data doesn't exist.
 */

bool Yaml::data_exist(std::string const &key) const
{
    return _config[key].IsDefined();
}