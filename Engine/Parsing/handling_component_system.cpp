/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** handling_component_system
*/

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif
#include "handling_component_system.hpp"

/**
 * @file handling_component_system.cpp
 */

using Component_System = IComponentSystem *(*)();

/**
 * @brief Construct a new handling component system::handling component system object
 *
 * @param libs_name List of the path of the library
 */

handling_component_system::handling_component_system(std::vector<std::string> const &libs_name)
{
    for (auto &lib_path : libs_name) {
        add_lib_component_system(lib_path);
    }
}

handling_component_system::~handling_component_system()
{
}

/**
 * @brief Add a library to the list of the library
 *
 * @param lib_path Path of the library
 */

void handling_component_system::add_lib_component_system(std::string const &lib_path)
{
    #ifdef _WIN32 // Windows
    HINSTANCE handle = LoadLibrary(lib_path.c_str());
    if (!handle) {
        throw std::runtime_error("error cannot open file: " + lib_path + "\n");
    }
    Component_System create = (Component_System)GetProcAddress(handle, "createComponentSystem");
    if (!create) {
        throw std::runtime_error("no function createComponentSystem \n");
    }
    #else // Linux
    void *handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("error cannot open file: " + lib_path + "\n");
    }
    Component_System create = (Component_System)dlsym(handle, "createComponentSystem");
    if (!create) {
        throw std::runtime_error("no function createComponentSystem \n");
    }
    #endif

    IComponentSystem *cs_data = create();
    if (cs_data == nullptr) {
        throw std::runtime_error("invalid createComponentSystem return invalid pointer\n");
    }
    cs_array.emplace_back(cs_data);
}

/**
 * @brief Check if the name is in the list of the library
 *
 * @param name Name of the library
 * @return true The name is in the list of the library
 * @return false The name is not in the list of the library
 */

bool handling_component_system::name_in_lib(std::string const &name) const noexcept
{
    for (auto &cs_data : cs_array)
        if (cs_data && cs_data->get_name() == name)
            return true;
    return false;
}

/**
 * @brief Load all the system of the library
 *
 * @param reg Registry of the ECS
 */

void handling_component_system::load_all_system(registry &reg) const noexcept
{
    for (auto &cs_data : cs_array)
        if (cs_data)
            cs_data->load_system(reg);
}

/**
 * @brief Load all the component of the library
 *
 * @param reg Registry of the ECS
 */

void handling_component_system::load_all_component(registry &reg) const noexcept
{
    for (auto &cs_data : cs_array)
        if (cs_data)
            cs_data->laod_component(reg);
}

/**
 * @brief Get the component system object
 *
 * @param key Name of the library
 * @return IComponentSystem* Pointer to the library
 */

IComponentSystem *handling_component_system::get_component_system(std::string const &key) noexcept
{
    for (auto &cs_data : cs_array) {
        if (cs_data && cs_data->get_name() == key)
            return cs_data.get();
    }
    return nullptr;
}