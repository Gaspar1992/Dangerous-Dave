#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class window {
public:
    
    window();
    window(const window& orig);
    virtual ~window();
    void setView(sf::View vista);
    void display();
    void draw(const sf::Drawable& drawable);
    bool isOpen();
    void close();
    void clear();
    void clear(sf::Color color);
    bool pollEvent(sf::Event &event);
    
private:
    sf::RenderWindow * ventana;
};

#endif /* WINDOW_HPP */

