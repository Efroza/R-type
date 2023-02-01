/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** data
*/

#ifndef DATA_HPP_
#define DATA_HPP_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <any>

class data
{
    public:
        data()
        {
            std::vector<sf::Texture> texture;
            db[std::type_index(typeid(sf::Texture))] = std::move(std::any(texture));
        }
        ~data() {}
        template <typename Type>
        bool type_exist()
        {
            return db.find(std::type_index(typeid(Type))) != db.end();
        }
        template <typename Type>
        std::vector<Type> &get_data()
        {
            if (type_exist<Type>() == false)
                throw std::runtime_error("error type does not exist");
            return std::any_cast<std::vector<Type> &>(db.at(std::type_index(typeid(Type))));
        }
        template <typename Type>
        Type &get_data(size_t id)
        {
            std::vector<Type> &data = get_data<Type>();

            if (id >= data.size())
                throw std::runtime_error("out of range");
            return data[id];
        }
        template <typename Type>
        size_t new_id()
        {
            std::vector<Type> &data = get_data<Type>();
            return data.size();
        }

        template <typename Type>
        void add_data(Type &&new_data)
        {
            std::vector<Type> &data = get_data<Type>();
            data.emplace_back(std::forward<Type>(new_data));
        }

    private:
        std::unordered_map<std::type_index, std::any> db;
};

#endif /* !DATA_HPP_ */