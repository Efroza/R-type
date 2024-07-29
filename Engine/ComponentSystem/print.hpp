/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** print
*/

#ifndef PRINT_HPP_
#define PRINT_HPP_

#include "IComponentSystem.hpp"

namespace component
{
    class print
    {
    };
};

namespace componentSystem
{
    class print : public IComponentSystem
    {
        public:
            print(/* args */);
            ~print();
            std::string get_name() const noexcept;
            void load_system(registry &reg) const noexcept;
            void laod_component(registry &reg) const noexcept;
            void add_entity_component(registry &reg, entity_t &e) const noexcept;
        private:
            std::string name;
    };
} // namespace name


#endif /* !PRINT_HPP_ */