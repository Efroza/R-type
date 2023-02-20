/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** left_deplacement
*/

#ifndef left_DEPLACEMENT_HPP_
#define left_DEPLACEMENT_HPP_

#include "ILoad_Interaction.hpp"

class left_deplacement : public ILoad_Interaction
{
    public:
        left_deplacement();
        ~left_deplacement();
        std::string get_name() const noexcept;
        interaction_function const &get_function() const noexcept;
    private:
        std::string name;
        interaction_function function;
};

#endif /* !left_DEPLACEMENT_HPP_ */