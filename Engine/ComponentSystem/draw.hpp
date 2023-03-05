/*
** EPITECH PROJECT, 2023
** Engine
** File description:
** draw
*/

#ifndef DRAW_HPP_
#define DRAW_HPP_

#include "IComponentSystem.hpp"

/**
 * @file draw.hpp
*/

namespace component
{
    class draw
    {
    };
}; // namespace component

namespace componentSystem {
    class draw : public IComponentSystem {
        public:
            draw(/* args */);
            ~draw();
            std::string get_name() const noexcept;
            void load_system(registry &reg) const noexcept;
            void laod_component(registry &reg) const noexcept;
            void add_entity_component(registry &reg, entity_t &e) const noexcept;

        private:
            /* data */
    };
}

#endif /* !DRAW_HPP_ */