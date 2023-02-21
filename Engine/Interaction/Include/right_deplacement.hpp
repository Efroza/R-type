/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** right_deplacement
*/

#ifndef right_DEPLACEMENT_HPP_
#define right_DEPLACEMENT_HPP_

#include "ILoad_Interaction.hpp"

class right_deplacement : public ILoad_Interaction
{
    public:
        right_deplacement();
        ~right_deplacement();
        std::string get_name() const noexcept;
        interaction_function const &get_function() const noexcept;
    private:
        std::string name;
        interaction_function function;
};

#endif /* !right_DEPLACEMENT_HPP_ */