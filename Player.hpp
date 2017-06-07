#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "sprite.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Bullet.hpp"
#include <iostream>

using namespace std;

class Player : public sf::Drawable {
public:
    Player();
    Player(const Player& orig);
    virtual ~Player();
    void update(int state, int vistaX);
    void setPosition(float x, float y);
    sf::FloatRect getGlobalbounds();
    sf::Vector2f getPosition();
    void movePlayer(sf::Vector2f velocidad);
    sf::Vector2f* getCollisionPoints();
    void setGun(bool x);
    bool CanYouAGun();
    sf::FloatRect getBulletBounds();
    bool ActiveBullet();
private:
    sf::Vector2f * CollisionPoints;
    sprite * player;
    sf::Clock * clock;
    sf::IntRect * rects;
    Bullet * bala;
    bool vista;
    bool arma;
    int after;
    void Derecha();
    void Izquierda();
    void Muerte();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(*player, states);
        if(bala!=NULL && bala->activa())
            target.draw(*bala, states);
    }
};

#endif /* PLAYER_HPP */

