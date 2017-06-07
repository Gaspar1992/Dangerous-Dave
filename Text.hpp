#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>

class Text : public sf::Drawable{
public:
    Text();
    Text(const Text& orig);
    virtual ~Text();
    void setFont(std::string archivo);
    void setSize(int size);
    void setPosition(float x,float y);
    void setString(std::string texto);
    void move(float x,float y);
    void setColor(sf::Color color);
    void setstyle(sf::Text::Style estilo);
private:
    
    sf::Font * font;
    sf::Text * text;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(*text, states);
    }
};

#endif /* TEXT_HPP */

