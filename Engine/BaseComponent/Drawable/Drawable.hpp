#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <string>
#include <utility>

class Drawable
{
public:
    Drawable(const std::string &str, const std::pair<int, int> &rect, bool isText);
    ~Drawable();

    const std::string &getStr() const;

    bool isText() const;
    std::pair<int, int> getRect() const;

private:
    std::string _str;
    std::pair<int, int> _rect;
    bool _isText;
};


#endif