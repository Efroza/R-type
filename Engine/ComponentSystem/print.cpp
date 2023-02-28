/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** print
*/

#include "print.hpp"
#include "IComponentSystem.hpp"
#include "rect.hpp"

componentSystem::print::print()
: name("print")
{
}

componentSystem::print::~print()
{
}

extern "C" IComponentSystem *createComponentSystem()
{
    return new componentSystem::print;
}

void system_print(registry &reg, sparse_array<component::rect> &position, sparse_array<component::print> &prints)
{
    for (size_t i = 0; i < prints.size(); ++i) {
        if (prints[i])
            ;
        // std::cout << "print" << std::endl;
    }
}

std::string componentSystem::print::get_name() const noexcept
{
    return name;
}

void componentSystem::print::load_system(registry &reg) const noexcept
{
    reg.add_system<component::rect, component::print>(system_print);
}

void componentSystem::print::laod_component(registry &reg) const noexcept
{
    reg.register_component<component::print>();
}

void componentSystem::print::add_entity_component(registry &reg, entity_t &e) const noexcept
{
    reg.add_component<component::print>(e, std::move(component::print()));
}