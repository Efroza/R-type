/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** up_deplacement
*/

#ifndef UP_DEPLACEMENT_HPP_
#define UP_DEPLACEMENT_HPP_

#include "ILoad_Interaction.hpp"

class up_deplacement : public ILoad_Interaction
{
    public:
        up_deplacement();
        ~up_deplacement();
        std::string get_name() const noexcept;
        interaction_function const &get_function() const noexcept;
    private:
        std::string name;
        interaction_function function;
};

#endif /* !UP_DEPLACEMENT_HPP_ */