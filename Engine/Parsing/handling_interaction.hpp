/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** handling_interaction
*/

#ifndef HANDLING_INTERACTION_HPP_
#define HANDLING_INTERACTION_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include "../Interaction/ILoad_Interaction.hpp"

class handling_interaction
{
    public:
        handling_interaction(std::vector<std::string> const &libs_name);
        handling_interaction(const handling_interaction &handling) = delete;
        handling_interaction(handling_interaction &&handling);
        ~handling_interaction();
        bool name_is_interaction(std::string const &name) const noexcept;
        ILoad_Interaction const *get_interaction(std::string const &key) const noexcept;
    private:
        void add_lib_interaction(std::string const &lib_path);

    private:
        std::vector<std::unique_ptr<ILoad_Interaction>> lib_interactions;
};

#endif /* !HANDLING_INTERACTION_HPP_ */
