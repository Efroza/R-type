/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-bsrtype-royale.badiabo
** File description:
** Parsor
*/

#ifndef PARSOR_HPP_
#define PARSOR_HPP_
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <json/value.h>
#include <string>
#include <boost/algorithm/string.hpp>
#include <vector>

class Parsor {
    public:
        Parsor(const std::string &path) {
            _file.open(path);
            if (!_file.is_open())
                throw std::runtime_error("Error: File not found");
            _entireFile.open(path);
        };

        ~Parsor() {
            _file.close();
            _entireFile.close();
        };

        void readEntireJson() {
            while (getline(_entireFile, _line)) {
                if (_line.empty())
                    continue;
                std::cout << _line << std::endl;
            }
        };

        void getJsonInfo(const std::string &info) {
            Json::Value root;
            Json::CharReaderBuilder read;

            if (!Json::parseFromStream(read, _file, &root, nullptr))
                throw std::runtime_error("Error: Can't parse file");
            for (auto &val : root)
                std::cout << '[' << val << ']' << std::endl;
            if (root[info].empty())
                throw std::runtime_error("Error: Can't find info");
            else
                std::cout << "" << std::endl; // << root[info] << std::endl;
        };

        Json::Value &getJson() {
            Json::CharReaderBuilder read;

            if (!Json::parseFromStream(read, _file, &_root, nullptr))
                throw std::runtime_error("Error: Can't parse file");
            return _root;
        }

    protected:
    private:
        Json::Value _root;
        Json::CharReaderBuilder _read;
        std::ifstream _file;
        std::ifstream _entireFile;
        std::string _line;
};

#endif /* !PARSOR_HPP_ */
