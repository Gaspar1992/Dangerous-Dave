#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "sprite.hpp"
#include "Bullet.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "window.hpp"

using namespace std;

class Enemy : public sf::Drawable{
public:
    Enemy();
    Enemy(const Enemy& orig);
    virtual ~Enemy();
    void update(sf::Time elapsedTime,int vistaX);
    sf::FloatRect getGlobalBounds();
    void setPosition(float x,float y);
    void posUpdate(float interpolacion);
    sf::Vector2f getInitialPosition();
    sf::Vector2f getPosition();
    bool isDead();
    void Dead();
    sf::FloatRect getBulletBounds();
    bool ActiveBullet();
private:
    sprite * enemy;
    bool ejeX,ejeY;
    bool muerto;
    Bullet * ataque;
    sf::Clock * Tmuerte;
    sf::Clock * atacar;
    sf::Vector2f * movimiento;
    sf::Vector2f * posPrev;
    sf::Vector2f * posNew;
    sf::Vector2f * initialPosition;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(*enemy, states);
        if(ataque!=NULL && ataque->activa())
            target.draw(*ataque, states);
    }
};

#endif /* ENEMY_HPP */

