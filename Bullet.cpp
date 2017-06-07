#include "Bullet.hpp"

Bullet::Bullet(float x,float y,bool derecha,int tipo) {
    bala = new sprite;
    bala->setPosition(x,y);
    velocidad = new sf::Vector2f;
    if(tipo==0){
    bala->setTexture("bullets.png");
        if(!derecha){
            bala->setTextureRect(sf::IntRect(19,0,19,12));
            velocidad->x = +4.f;
        }else{
            bala->setTextureRect(sf::IntRect(0,0,19,12));
            velocidad->x = -4.f;
        }
    }else{
       bala->setTexture("attack.png");
       velocidad->x = -8.f;
    }
    
    
    Activa = false;
    
}

Bullet::Bullet(const Bullet& orig) {
}

Bullet::~Bullet() {
    delete bala;
    delete velocidad;
}
sf::FloatRect Bullet::getGlobalBounds(){
    return bala->getGlobalBounds();
}

void Bullet::update(){
    //BALA RECIEN ACTIVADA
    if(!Activa){
        Activa = true;
    }
    //ACTUALIZAR BALA
    else if(Activa)
        bala->move(velocidad->x,velocidad->y);
}
bool Bullet::activa(){
    return Activa;
}
float Bullet::getXPosition(){
    return bala->getPosition().x;
}