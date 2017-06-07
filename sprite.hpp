#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>

class sprite : public sf::Drawable {
public:
    sprite();
    sprite(const sprite& orig);
    void setTexture(std::string archivo);
    void setPosition(float x, float y);
    void setColor(sf::Color color);
    sf::FloatRect getGlobalBounds();
    void scale(float x,float y);
    void setTextureRect(sf::IntRect rect);
    virtual ~sprite();
    sf::Vector2f getPosition();
    void move(float x,float y);
    void rotate(float angle);
    void setScale(float x,float y);
    void setOrigin(float x,float y);
private:
    sf::Sprite * p_sprite;
    sf::Texture * p_texture;
    
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(*p_sprite, states);
    }
};

#endif /* SPRITE_HPP */

