/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** down_deplacement
*/

#ifndef down_DEPLACEMENT_HPP_
#define down_DEPLACEMENT_HPP_

#include "ILoad_Interaction.hpp"

class down_deplacement : public ILoad_Interaction
{
    public:
        down_deplacement();
        ~down_deplacement();
        std::string get_name() const noexcept;
        interaction_function const &get_function() const noexcept;
    private:
        std::string name;
        interaction_function function;
};

#endif /* !down_DEPLACEMENT_HPP_ */