/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** ILoad_Interaction
*/

#ifndef ILOAD_INTERACTION_HPP_
#define ILOAD_INTERACTION_HPP_

#include <iostream>
#include <functional>
#include "registry.hpp"

class ILoad_Interaction {
    public:
        using interaction_function = std::function<void(entity_t &e, registry &reg)>;
    public:
        ~ILoad_Interaction() = default;
        virtual std::string get_name() const noexcept = 0;
        virtual interaction_function const &get_function() const noexcept = 0;
    protected:
    private:
};

#endif /* !ILOAD_INTERACTION_HPP_ */
