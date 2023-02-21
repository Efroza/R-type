/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** handling_component_system
*/

#ifndef HANDLING_COMPONENT_SYSTEM_HPP_
#define HANDLING_COMPONENT_SYSTEM_HPP_

#include <vector>
#include <iostream>
#include "IComponentSystem.hpp"

class handling_component_system
{
    public:
        handling_component_system(std::vector<std::string> const &libs_name);
        ~handling_component_system();
        void add_lib_component_system(std::string const &pathlib);
        IComponentSystem const *get_component_system(std::string const &key) const noexcept;
        bool name_in_lib(std::string const &name) const noexcept;
        void load_all_system(registry &reg) const noexcept;
        void load_all_component(registry &reg) const noexcept;

    private:
        std::vector<std::unique_ptr<IComponentSystem>> cs_array;
        /* data */
};


#endif /* !HANDLING_COMPONENT_SYSTEM_HPP_ */