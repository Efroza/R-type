/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Yaml
*/

#include "Yaml.hpp"

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

std::vector<std::string> Yaml::get(std::string const &info) const
{
    try {
        return _config[info].as<std::vector<std::string>>();
    } catch (const std::exception &e) {
        throw std::runtime_error("Can't get this info from that config file");
    }
}

bool Yaml::data_exist(std::string const &key) const
{
    return _config[key].IsDefined();
}