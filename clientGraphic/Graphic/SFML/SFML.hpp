#ifndef SFML_HPP
#define SFML_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "../AGraphic.hpp"

typedef struct SFMLObject_s
{
    sf::IntRect rect;
    sf::Texture texture;
    std::unique_ptr<sf::Text> text;
    std::unique_ptr<sf::Sprite> sprite;
    bool isText;
} SMFLObject_t;

class SFML : public AGraphic
{
public:
    SFML();
    ~SFML();

    void initialize(int x, int y, const std::string &name) final;
    void destroy() final;
    void clearWindow() final;
    void refreshWindow() final;
    void draw(std::shared_ptr<Drawable> image, const std::pair<int, int> &position) final;
    events_e pollEvent() final;
    
private:
    void load(std::shared_ptr<Drawable> image);

    std::shared_ptr<sf::RenderWindow> _window;
    sf::Event _event;
    std::map<std::string, SMFLObject_t> _db;
    static const std::map<int, events_e> _confButton;
};

#endif