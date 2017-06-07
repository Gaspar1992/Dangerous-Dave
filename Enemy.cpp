#include "Enemy.hpp"

Enemy::Enemy() {
    enemy = new sprite;
    enemy->setTexture("arana.png");
    movimiento = new sf::Vector2f;
    movimiento->x = 150.f;
    movimiento->y = 40.f;
    ataque = NULL;
    posPrev = new sf::Vector2f;
    posNew = new sf::Vector2f;
    initialPosition = NULL;
    ejeX = false;
    ejeY = false;
    muerto = false;
    Tmuerte = NULL;
    atacar = new sf::Clock;
}

Enemy::Enemy(const Enemy& orig) {
}

Enemy::~Enemy() {
    delete enemy;
    delete ataque;
    delete Tmuerte;
    delete atacar;
    delete movimiento;
    delete posPrev;
    delete posNew;
    delete initialPosition;
}
/*INTERPOLACION*/
void Enemy::update(sf::Time elapsedTime,int vistaX){
    if(Tmuerte==NULL && !muerto){
        /****************** INTERPOLACION(2) *********************/
        posPrev = posNew;
        //EJE X
        if(initialPosition->x+490<enemy->getPosition().x && !ejeX)
            ejeX=true;
        if(initialPosition->x+500>=enemy->getPosition().x && !ejeX)
            posNew->x += movimiento->x * elapsedTime.asSeconds();
        else if(initialPosition->x+10>enemy->getPosition().x && ejeX)
            ejeX = false;
        else
            posNew->x -= movimiento->x * elapsedTime.asSeconds();

        //EJE Y
        if(initialPosition->y+40<enemy->getPosition().y && !ejeY)
            ejeY=true;
        if(initialPosition->y+50>=enemy->getPosition().y && !ejeY)
            posNew->y += movimiento->y * elapsedTime.asSeconds();
        else if(initialPosition->y+10>enemy->getPosition().y && ejeY)
            ejeY = false;
        else
            posNew->y -= movimiento->y * elapsedTime.asSeconds();
        
        //ATAQUE DE LA ARAÑA
        if(ataque!=NULL){
            ataque->update();
            if(ataque->getXPosition()<vistaX || ataque->getXPosition()>vistaX+640){
                delete ataque; ataque = NULL;
            }
        }
        else if(atacar->getElapsedTime().asSeconds()>4 && ataque==NULL  && 
                (enemy->getPosition().x>vistaX && enemy->getPosition().x < vistaX+640)){
            float x,y;
            x = enemy->getPosition().x;
            y = enemy->getPosition().y+enemy->getGlobalBounds().height/2;
            ataque = new Bullet(x,y,false,1);
            atacar->restart();
        }
        
    }else{
        //ANIMACION Y MUERTE DEL NPC
        if(atacar!=NULL){
            delete ataque;
            ataque = NULL;
        }   
        if(Tmuerte->getElapsedTime().asSeconds()>0 && Tmuerte->getElapsedTime().asSeconds()<0.1){
            enemy->setTexture("player.png");
            enemy->setTextureRect(sf::IntRect(256,0,64,64));
        }
        if(Tmuerte->getElapsedTime().asSeconds()>sf::seconds(0.2).asSeconds()) {
            enemy->setScale(0.5,0.5);
        }
        if(Tmuerte->getElapsedTime().asSeconds()>sf::seconds(0.4).asSeconds()) {
            enemy->setScale(0.4,0.4);
        }
        if(Tmuerte->getElapsedTime().asSeconds()>sf::seconds(0.6).asSeconds()) {
            enemy->setScale(0.3,0.3);
        }
        if(Tmuerte->getElapsedTime().asSeconds()>sf::seconds(0.8).asSeconds()) {
            enemy->setScale(0.5,0.5);
            delete Tmuerte;Tmuerte = NULL;
            muerto = true;
        }
    }
    
    
}

sf::FloatRect Enemy::getGlobalBounds(){
    return enemy->getGlobalBounds();
}
/*INTERPOLACION*/
void Enemy::posUpdate(float interpolacion){
    /****************** INTERPOLACION(3) *********************/
    sf::Vector2f renderPos;
    renderPos.x = posPrev->x + ((posNew->x-posPrev->x) * interpolacion);
    renderPos.y = posPrev->y + ((posNew->y - posPrev->y)* interpolacion);
    enemy->setPosition(renderPos.x,renderPos.y);
}
void Enemy::setPosition(float x, float y){
    enemy->setPosition(x,y);
    *posPrev = sf::Vector2f(x,y);
    *posNew = sf::Vector2f(x,y);
    if(initialPosition==NULL){
        initialPosition = new sf::Vector2f;
        *initialPosition = sf::Vector2f(x,y);
    }
}
sf::Vector2f Enemy::getInitialPosition(){return *initialPosition;}

sf::Vector2f Enemy::getPosition(){return enemy->getPosition();}
void Enemy::Dead(){
    if(!muerto)
        Tmuerte = new sf::Clock;
}
bool Enemy::isDead(){return muerto;}
sf::FloatRect Enemy::getBulletBounds(){
        return ataque->getGlobalBounds();
}
bool Enemy::ActiveBullet(){
    if(ataque!=NULL)
        return true;
    return false;
}