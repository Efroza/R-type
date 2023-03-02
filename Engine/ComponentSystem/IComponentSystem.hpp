/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** IComponentSystem
*/

#ifndef ICOMPONENTSYSTEM_HPP_
#define ICOMPONENTSYSTEM_HPP_

#include <iostream>
#include <cctype>
#include "../Include/registry.hpp"

class IComponentSystem {
    public:
        ~IComponentSystem() = default;
        virtual std::string get_name() const noexcept = 0;
        virtual void load_system(registry &reg) const noexcept = 0;
        virtual void laod_component(registry &reg) const noexcept = 0;
        virtual void add_entity_component(registry &reg, entity_t &e) const noexcept = 0;

    protected:
    private:
};

#endif /* !ICOMPONENTSYSTEM_HPP_ */

