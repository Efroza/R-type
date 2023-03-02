/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <any>
#include <functional>

#include "sparse_array.hpp"
#include "entity.hpp"

class registry
{
    public:
        registry()
        {
        }
        template <class Component>
        sparse_array<Component> &register_component()
        {std::any new_components = sparse_array<Component>();_components_arrays[std::type_index(typeid(Component))] = std::move(new_components);_erase_component.push_back([&](entity_t e){    auto &array = get_components<Component>();    array.erase(e._id);});return std::any_cast<sparse_array<Component> &>(_components_arrays.at(std::type_index(typeid(Component))));
        }
        template <class Component>
        sparse_array<Component> &get_components()
        {
            if (_components_arrays.find(std::type_index(typeid(Component))) == _components_arrays.end())
                throw std::runtime_error("errror invalid component");
            return std::any_cast<sparse_array<Component> &>(_components_arrays.at(std::type_index(typeid(Component))));
        }
        template <class Component>
        sparse_array<Component> const &get_components() const
        {
            if (_components_arrays.find(std::type_index(typeid(Component))) == _components_arrays.end())
                throw std::runtime_error("errror invalid component");
            return std::any_cast<sparse_array<Component> const &>(_components_arrays.at(std::type_index(typeid(Component))));
        }
        entity_t spawn_entity()
        {
            entity_t new_entity = _entity_container.size();
            if (_kill.empty() == false) {
                new_entity = _kill.front();
                _kill.erase(_kill.begin());
            }
            _entity_container.emplace_back(std::move(new_entity));
            return _entity_container.back();
        }
        entity_t entity_from_index(std ::size_t idx)
        {
            if (_entity_container.size() <= idx)
                throw std::runtime_error("out of range");
            return _entity_container[idx];
        }
        bool is_kill(entity_t const &e)
        {
            for (auto &id : _kill)
                if (id == e._id)
                    return true;
            return false;
        }

        void kill_entity(entity_t const &e)
        {
            if (is_kill(e))
                return;
            _kill.push_back(e._id);
            for (auto &erase_fun : _erase_component) {
                erase_fun(e);
            }
        }

        template <typename Component>
        typename sparse_array<Component>::reference_type add_component(entity_t const &to,
                                                                       Component &&c)
        {
            if (to._id > _entity_container.size())
                throw std::runtime_error("invalid entity id");
            sparse_array<Component> &array = get_components<Component>();
            return array.insert_at(to._id, std::forward<Component>(c));
        }
        template <typename Component, typename... Params>
        typename sparse_array<Component>::reference_type emplace_component(entity_t const &to, Params &&...p)
        {
            if (to._id > _entity_container.size())
                throw std::runtime_error("invalid entity id");
            sparse_array<Component> &array = get_components<Component>();
            return array.emplace_at(to._id, std::forward<Params>(p)...);
        }
        template <typename Component>
        void remove_component(entity_t const &from)
        {
            if (from._id > _entity_container.size())
                throw std::runtime_error("invalid entity id");
            sparse_array<Component> &array = get_components<Component>();
            array.erase(from._id);
        }
        template <class... Components, typename Function>
        void add_system(Function &&f)
        {
            _systemes.push_back(
                [&](registry &reg)
                {
                    f(reg, get_components<Components>() ...);
                });
        }
        template <class... Components, typename Function>
        void add_system(Function const &f)
        {
            _systemes.push_back(
                [&](registry &reg)
                {
                    f(reg, get_components<Components>()...);
                });
        }
        void run_systems()
        {
            for (auto &system : _systemes) {
                system(*this);
            }
        }

    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::vector<entity_t> _entity_container;
        std::vector<std::uint32_t> _kill;
        std::vector<std::function<void(entity_t)>> _erase_component;
        std::vector<std::function<void (registry &)>> _systemes;
};

#endif /* !REGISTRY_HPP_ */