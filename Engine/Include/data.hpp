/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-luc1.schmitt
** File description:
** data
*/

#ifndef DATA_HPP_
#define DATA_HPP_

#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <any>
#include <list>
#include "entity.hpp"

class data
{
public:
    data()
    {
    }
    ~data() {}
    template <typename Type>
    bool type_exist()
    {
        return db.find(std::type_index(typeid(Type))) != db.end();
    }
    template <typename Type>
    void add_list_data()
    {
        std::list<Type> list;
        db[std::type_index(typeid(Type))] = std::move(std::any(list));
    }

    template <typename Type>
    std::list<Type> &get_data()
    {
        if (type_exist<Type>() == false)
            throw std::runtime_error("error type does not exist");
        return std::any_cast<std::list<Type> &>(db.at(std::type_index(typeid(Type))));
    }
    template <typename Type>
    Type &get_data(size_t id)
    {
        std::list<Type> &data = get_data<Type>();

        if (id >= data.size())
            throw std::runtime_error("out of range");
        auto elem = data.begin();
        std::advance(elem, id);
        return *elem;
    }
    template <typename Type>
    size_t new_id()
    {
        std::list<Type> &data = get_data<Type>();
        return data.size();
    }

    template <typename Type>
    void add_data(Type &&new_data)
    {
        std::list<Type> &data = get_data<Type>();
        data.emplace_back(std::forward<Type>(new_data));
    }
    template <typename Type>
    void insert_data(Type &&new_data, const entity_t &entity)
    {
        size_t id = entity._id;
        std::list<Type> &data = get_data<Type>();

        if (data.size() <= id)
            data.resize(id + 1);
        auto elem = data.begin();
        std::advance(elem, id);
        data.insert(elem, std::forward<Type>(new_data));
    }
    template <typename Type>
    void insert_data(Type &&new_data, size_t id)
    {
        std::list<Type> &data = get_data<Type>();

        std::cout << "id[" << id << "]" << std::endl;
        if (data.size() <= id)
            data.resize(id + 1);
        auto elem = data.begin();
        std::advance(elem, id);
        data.insert(elem, std::forward<Type>(new_data));
    }
    template <typename Type>
    bool data_exist(size_t id)
    {
        if (type_exist<Type>() == false)
            return false;
        std::list<Type> &all_data = get_data<Type>();
        return all_data.size() > id;
    }

private:
    std::unordered_map<std::type_index, std::any> db;
};

#endif /* !DATA_HPP_ */