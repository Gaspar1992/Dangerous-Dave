#ifndef FOOTER_HPP
#define FOOTER_HPP

#include "sprite.hpp"
#include "Text.hpp"
#include <SFML/Graphics.hpp>

class footer : public sf::Drawable{
public:
    footer();
    footer(const footer& orig);
    virtual ~footer();
    void move(int x,int y);
    void TakeGun(bool x);
    void TakeKey(bool x);
    void PreGame();
    void Game();
private:
    sprite * Footer;
    sprite * gun;
    sprite * door;
    Text * text;
    bool pregame;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(*Footer, states);
        target.draw(*text, states);
        if(gun!=NULL)
            target.draw(*gun, states);
        if(door!=NULL)
            target.draw(*door, states);
    }
};

#endif /* FOOTER_HPP */

