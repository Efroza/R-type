/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** handling_component_system
*/

#include "handling_component_system.hpp"
#include <dlfcn.h>

using Component_System = Component_System *(*)();

handling_component_system::handling_component_system(std::vector<std::string> const &libs_name)
{
}

handling_component_system::~handling_component_system()
{
}

void handling_component_system::add_lib_component_system(std::string const &lib_path)
{
    void *handle = dlopen(lib_path.c_str(), RTLD_LAZY);

    if (handle == nullptr)
        throw std::runtime_error("error cannot open file\n");
    Component_System create = (Component_System)dlsym(handle, "createComponentSystem");
    if (create == nullptr)
        throw std::runtime_error("no function createComponentSystem \n");
    Component_System *cs_data = create();
    if (cs_data == nullptr)
        throw std::runtime_error("invalid createComponentSystem return invalid pointer\n");
    cs_array.emplace_back(cs_data);
}

bool handling_component_system::name_in_lib(std::string const &name) const noexcept
{
    for (auto &cs_data : cs_array)
        if (cs_data && cs_data->get_name() == name)
            return true;
    return false;
}

void handling_component_system::load_all_system(registry &reg) const noexcept
{
    for (auto &cs_data : cs_array)
        if (cs_data)
            cs_data->load_system(reg);
}

void handling_component_system::load_all_component(registry &reg) const noexcept
{
    for (auto &cs_data : cs_array)
        if (cs_data)
            cs_data->laod_component(reg);
}

IComponentSystem const *handling_component_system::get_component_system(std::string const &key) const noexcept
{
    for (auto &cs_data : cs_array) {
        if (cs_data && cs_data->get_name() == key)
            cs_data.get();
    }
    return nullptr;
}