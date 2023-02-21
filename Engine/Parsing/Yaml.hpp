/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** Yaml
*/

#ifndef YAML_HPP_
#define YAML_HPP_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/node/node.h>

class Yaml {
    public:
        Yaml(std::string);
        ~Yaml();
        std::vector<std::string> get(std::string) const;

    protected:
    private:
        YAML::Node _config;

};

#endif /* !YAML_HPP_ */
