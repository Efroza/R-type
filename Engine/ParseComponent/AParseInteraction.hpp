/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** AParseInteraction
*/

#ifndef APARSEINTERACTION_HPP_
#define APARSEINTERACTION_HPP_

#include "../Parsing/handling_interaction.hpp"

class AParseInteraction {
    public:
        AParseInteraction();
        ~AParseInteraction();
        void set_interaction(handling_interaction &interaction) noexcept;
        handling_interaction const *get_interaction() noexcept;

    protected:
        handling_interaction *_interaction;

    private:
};

#endif /* !APARSEINTERACTION_HPP_ */
