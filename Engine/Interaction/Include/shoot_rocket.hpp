/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** shoot_rocket
*/

#ifndef SHOOT_ROCKET_HPP_
#define SHOOT_ROCKET_HPP_

#include "../ILoad_Interaction.hpp"

class shoot_rocket : public ILoad_Interaction
{
    public:
        shoot_rocket();
        ~shoot_rocket();
        std::string get_name() const noexcept;
        interaction_function const &get_function() const noexcept;

    private:
        std::string name;
        interaction_function function;
};

#endif /* !SHOOT_ROCKET_HPP_ */
