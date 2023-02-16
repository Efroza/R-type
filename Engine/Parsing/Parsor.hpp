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
            if (root[info].empty())
                throw std::runtime_error("Error: Can't find info");
            else
                std::cout << root[info] << std::endl;
        };

        // template <typename... T>
        // void getJsonInfo(T... args) {
        //     constexpr auto size = sizeof...(args);
        //     std::string arr[size] = {args...};
        //     std::vector<std::string> res;

        //     if (!Json::parseFromStream(_read, _file, &_root, nullptr))
        //         throw std::runtime_error("Error: Can't parse file");
        //     for (size_t i = 0; i < size; i++) {
        //         std::cout << arr[i] << std::endl;
        //         boost::split(res, arr[i], boost::is_any_of(";"));
        //         for (auto &it : res)
        //             std::cout << it << std::endl;

        //         // if (_root[arr[i]].empty())
        //         //     throw std::runtime_error("Error: Can't find info");
        //         // else
        //         //     std::cout << _root[arr[i]] << std::endl;
        //     }
        // };

    protected:
    private:
        Json::Value _root;
        Json::CharReaderBuilder _read;
        std::ifstream _file;
        std::ifstream _entireFile;
        std::string _line;
};

#endif /* !PARSOR_HPP_ */
