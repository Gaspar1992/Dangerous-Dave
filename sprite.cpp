#include "sprite.hpp"

sprite::sprite() {
    p_sprite = new sf::Sprite;
    p_texture = new sf::Texture;
}

sprite::sprite(const sprite& orig) {
}
void sprite::setColor(sf::Color color){
    p_sprite->setColor(color);
}
sprite::~sprite() {
    delete p_sprite;
    delete p_texture;
}

void sprite::setTexture(std::string archivo) {
    p_texture->loadFromFile("resources/"+archivo);
    p_sprite->setTexture(*p_texture);
}

void sprite::setPosition(float x, float y) {
    p_sprite->setPosition(x,y);
}

sf::FloatRect sprite::getGlobalBounds() {
    return p_sprite->getGlobalBounds();
}

void sprite::scale(float x, float y) {
    p_sprite->scale(x, y);
}

void sprite::setTextureRect(sf::IntRect rect) {
    p_sprite->setTextureRect(rect);
}
sf::Vector2f sprite::getPosition() {return p_sprite->getPosition();}

void sprite::move(float x, float y) {
    p_sprite->move(x,y);
}
void sprite::rotate(float angle){
    p_sprite->rotate(angle);
}
void sprite::setScale(float x, float y){
    p_sprite->setScale(x,y);
}
void sprite::setOrigin(float x, float y){
    p_sprite->setOrigin(x,y);
}