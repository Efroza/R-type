/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** sparse_array
*/


#ifndef SPARSE_ARRAY_HPP_
#define SPARSE_ARRAY_HPP_

#include <optional>
#include <cinttypes>
#include <iterator>
#include <algorithm>
#include <memory>
#include <vector>

template <typename Component> // You can also mirror the definition of std :: vector ,
// that takes an additional allocator.
class sparse_array
{
public:
    using value_type = std::optional<Component>; //? ? ? ; // optional component type
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std ::vector<value_type>; // optionally add your allocator
    using unused_container = std::vector<std::uint8_t>; // vector who get all unused ids
    // template here.
    using size_type = typename container_t ::size_type;
    using iterator = typename container_t ::iterator;
    using const_iterator = typename container_t ::const_iterator;

public:
    sparse_array(){};                                          // You can add more constructors .
    sparse_array(sparse_array const &array) { *this = array; } // copy constructor
    sparse_array(sparse_array &&array) noexcept
    {
        *this = array;
    } // move constructor
    ~sparse_array() {}
    sparse_array &operator=(sparse_array const &array)
    {
        _data = array._data;
        return *this;
    } // copy assignment operator
    sparse_array &operator=(sparse_array &&array) noexcept
    {
        _data = std::move(array._data);
        return *this;
    } // move assignment operator
    reference_type operator[](size_t idx)
    {
        return _data[idx];
    }
    const_reference_type operator[](size_t idx) const
    {
        return _data[idx];
    }
    iterator begin()
    {
        return _data.begin();
    }
    const_iterator begin() const
    {
        return _data.begin();
    }
    const_iterator cbegin() const
    {
        return _data.cbegin();
    }
    iterator end()
    {
        return _data.begin();
    }
    const_iterator end() const
    {
        return _data.end();
    }
    const_iterator cend() const
    {
        return _data.cend();
    }
    size_type size() const
    {
        return _data.size();
    }
    bool exist(size_type pos) const
    {
        if (_data.at(pos))
            return true;
        return false;
    }
    // a coder
    reference_type insert_at(size_type pos, Component const &entity)
    {
        if (_data.size() <= pos)
            _data.resize(pos + 1);
        _data[pos] = entity;
        return _data[pos];
    }
    reference_type insert_at(size_type pos, Component &&entity)
    {
        if (_data.size() <= pos)
            _data.resize(pos + 1);
        _data[pos] = std::move(entity);
        return _data[pos];
    }
    template <class... Params>
    reference_type emplace_at(size_type pos, Params &&...params)
    {
        if (pos >= _data.size()) {
            _data.resize(pos + 1);
        }
        auto allocator = _data.get_allocator();
        std::allocator_traits<std::allocator<Component>>::destroy(allocator, &(*(_data.begin() + pos)));
        std::allocator_traits<std::allocator<Component>>::construct(allocator, &(*(_data.begin() + pos)), std::forward<Params>(params)...);
        return (_data[pos]);
    } // optional
    void erase(size_type pos)
    {
        if (pos < 0  || pos > _data.size())
            return;
        _data[pos] = std::nullopt;
    }
    size_type get_index(value_type const &entity) const
    {
        for (size_type i = 0; i < _data.size(); ++i)
        {
            if (_data[i] == entity)
                return i;
        }
        return 0;
    }

private:
    container_t _data;
};
#endif /* !SPARSE_ARRAY_HPP_ */