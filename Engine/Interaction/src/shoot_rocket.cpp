/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** shoot_rocket
*/

/**
 * @file shoot_rocket.cpp
 */

#include "../ILoad_Interaction.hpp"
#include "../Include/shoot_rocket.hpp"
#include "../../BaseComponent/position.hpp"
#include "../../BaseComponent/network_player.hpp"

/**
 * @brief Create a Interaction object
 *
 * @return ILoad_Interaction*
 * @details This function is called by the plugin loader to create a new instance of the plugin
 */
#ifdef _WIN32
extern "C" __declspec(dllexport) ILoad_Interaction *createInteraction()
{ 
    return new shoot_rocket;
}
#else
extern "C" ILoad_Interaction *createInteraction()
{
    return new shoot_rocket;
}
#endif

/**
 * @brief Function called when the interaction is triggered
 *
 * @param e The entity that triggered the interaction
 * @param reg The registry of the game
 * @details This function will make the entity move right by 20 pixels
 */

void shoot_rocket_function(entity_t &e, registry &reg)
{
    entity_t rocket = reg.spawn_entity();
    reg.add_component<component::position>(rocket, std::move(component::position(500, 500)));
    reg.add_component<component::network_player>(rocket, std::move(component::network_player()));
    std::cout << "SHOOOOOOOOT" << std::endl;
}

shoot_rocket::shoot_rocket()
    : name("shoot_rocket"), function(shoot_rocket_function)
{
}

shoot_rocket::~shoot_rocket()
{
}

/**
 * @brief Get the Name object
 *
 * @return std::string
 * @details This function will return the name of the interaction
 */

std::string shoot_rocket::get_name() const noexcept
{
    return name;
}

/**
 * @brief Get the Function object
 *
 * @return ILoad_Interaction::interaction_function
 * @details This function will return the function of the interaction
 */

ILoad_Interaction::interaction_function const &shoot_rocket::get_function() const noexcept
{
    return function;
}
