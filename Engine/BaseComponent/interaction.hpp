/*
** EPITECH PROJECT, 2023
** JAM-1-2023
** File description:
** interaction
*/

#ifndef INTERACTION_HPP_
#define INTERACTION_HPP_
#include <functional>
#include <unordered_map>
#include <cinttypes>
#include "../Include/entity.hpp"
#include "../Include/registry.hpp"

namespace component {
    class interaction
    {
        public:
            using interaction_function = std::function<void(entity_t &e, registry &reg)>;

        public:
            interaction(/* args */);
            ~interaction();
            void new_interaction(std::uint8_t type, const interaction_function &fun) noexcept;
            void delete_interaction(std::uint8_t type);
            void trigger_interaction(std::uint8_t type, entity_t &e, registry &reg) const;
            bool type_is_register(std::uint8_t type) const noexcept;
            void set_typing(std::uint8_t type) noexcept;
            std::vector<std::uint8_t> const &get_typing() const noexcept;
            void empty_typing() noexcept;

        private:
            std::unordered_map<std::uint8_t, interaction_function> _handling;
        public:
            std::vector<std::uint8_t> typing;
    };
}

#endif /* !INTERACTION_HPP_ */
