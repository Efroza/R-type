/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** handling_interaction
*/

#include "handling_interaction.hpp"
#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif

using function_interaction = ILoad_Interaction *(*)();

// int main(void)
// {
//     void *handle = dlopen("../Interaction/up_deplacement.so", RTLD_LAZY);

//     if (handle == nullptr)
//         throw std::runtime_error("error cannot open file\n");
//     function_interaction create = (function_interaction)dlsym(handle, "createInteraction");
//     if (create == nullptr)
//         throw std::runtime_error("no function createInteraction \n");
//     ILoad_Interaction *interaction = create();
//     if (interaction == nullptr)
//         throw std::runtime_error("invalid createInteraction return invalid pointer\n");
//     std::cout << interaction->get_name() << std::endl;
// }

handling_interaction::handling_interaction(std::vector<std::string> const &libs_name)
{
    for (auto &lib_name : libs_name)
        try {
            add_lib_interaction(lib_name);
        } catch (std::exception const &e)
        {
            std::cerr << e.what() << std::endl;
        }
}

handling_interaction::handling_interaction(handling_interaction &&handling) : lib_interactions(std::move(handling.lib_interactions))
{
    for (auto &lib : handling.lib_interactions)
    {
        ILoad_Interaction const *ptr = lib.release();
        lib_interactions.emplace_back(lib.release());
    }
}

handling_interaction::~handling_interaction()
{
}

bool handling_interaction::name_is_interaction(std::string const &name) const noexcept
{
    for (auto &lib : lib_interactions) {
        if (name == lib->get_name())
            return true;
    }
    return false;
}

void handling_interaction::add_lib_interaction(std::string const &lib_path)
{
    #ifdef _WIN32 // Windows
    HINSTANCE handle = LoadLibrary(lib_path.c_str());
    if (!handle) {
        throw std::runtime_error("error cannot open file: " + lib_path + "\n");
    }
    function_interaction create = (function_interaction)GetProcAddress(handle, "createInteraction");
    if (!create) {
        throw std::runtime_error("no function createInteraction \n");
    }
    #else // Linux
    void *handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("error cannot open file: " + lib_path + "\n");
    }
    function_interaction create = (function_interaction)dlsym(handle, "createInteraction");
    if (!create) {
        throw std::runtime_error("no function createInteraction \n");
    }
    #endif

    ILoad_Interaction *interaction = create();
    if (interaction == nullptr) {
        throw std::runtime_error("invalid createInteraction return invalid pointer\n");
    }
    lib_interactions.emplace_back(std::unique_ptr<ILoad_Interaction>(interaction));
}

ILoad_Interaction const *handling_interaction::get_interaction(std::string const &name) const noexcept
{
    for (auto &lib : lib_interactions) {
        if (name == lib->get_name())
            return lib.get();
    }
    return nullptr;
}