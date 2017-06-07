#ifndef BULLET_HPP
#define BULLET_HPP

#include "sprite.hpp"
#include <SFML/Graphics.hpp>

class Bullet : public sf::Drawable{
public:
    Bullet(float x,float y,bool derecha,int tipo);
    Bullet(const Bullet& orig);
    virtual ~Bullet();
    void update();
    sf::FloatRect getGlobalBounds();
    bool activa();
    float getXPosition();
private:
    sprite * bala;
    bool Activa;
    sf::Vector2f * velocidad;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(*bala, states);
    }
};

#endif /* BULLET_HPP */

