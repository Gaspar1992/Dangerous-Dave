#include "Player.hpp"

Player::Player() {
    arma = false;
    bala = NULL;
    clock = new sf::Clock;
    player = new sprite;
    player->setTexture("player.png");
    player->scale(0.5,0.5);
    player->setPosition(0,0);
    rects = new sf::IntRect[8];
    for(int i=0;i<8;i++) {
        if(i==0){// QUIETO DERECHA
            rects[i] = sf::IntRect(0,0,64,64);
        }
        if(i==1){// PASO DERECHA
            rects[i] = sf::IntRect(64,0,64,64);
        }
        if(i==2){//SALTO DERECHA
            rects[i] = sf::IntRect(128,0,64,64);
        }
        if(i==3){//REINICIO
            rects[i] = sf::IntRect(192,0,64,64);
        }
        if(i==4){//MUERTE
            rects[i] = sf::IntRect(256,0,64,64);
        }
        if(i==5){// QUIETO IZQUIERDA
            rects[i] = sf::IntRect(320,64,64,64);
        }
        if(i==6){// PASO IZQUIERDA
            rects[i] = sf::IntRect(256,64,64,64);
        }
        if(i==7){// SALTO IZQUIERDA
            rects[i] = sf::IntRect(192,64,64,64);
        }
    }
    //SPRITE INICIAL
    player->setTextureRect(rects[3]);
    
    //PUNTOS DE COLISION DEL SPRITE
    CollisionPoints = new sf::Vector2f[8];
    for(int i=0;i<8;i++){
        if(i==0){
            CollisionPoints[i] = sf::Vector2f(0,0);
        }
        if(i==1){
            CollisionPoints[i] = sf::Vector2f(player->getGlobalBounds().width/2,0);
        }
        if(i==2){
            CollisionPoints[i] = sf::Vector2f(player->getGlobalBounds().width,0);
        }
        if(i==3){
            CollisionPoints[i] = sf::Vector2f(0,player->getGlobalBounds().height/2);
        }
        if(i==4){
            CollisionPoints[i] = sf::Vector2f(player->getGlobalBounds().width,player->getGlobalBounds().height/2);
        }
        if(i==5){
            CollisionPoints[i] = sf::Vector2f(0,player->getGlobalBounds().height);
        }
        if(i==6){
            CollisionPoints[i] = sf::Vector2f(player->getGlobalBounds().width/2,player->getGlobalBounds().height);
        }
        if(i==7){
            CollisionPoints[i] = sf::Vector2f(player->getGlobalBounds().width,player->getGlobalBounds().height);
        }
    }
    vista = false;    
}

Player::Player(const Player& orig) {
}

Player::~Player() {
    
}
void Player::update(int state, int vistaX) {
    /*
     * ESTADOS
     * 0 = quieto
     * 1 = derecha
     * 2 = izquierda
     * 3 = agachado
     * 4 = muerte
     * 5 = disparo
     * 6 = Caida
     * 7 = reboot
     * //ESTADOS MEDIOS
     * 
     * 13 && 23 = SALTANDO MIENTRAS ANDA / CORREGIR ANIMACION
     * VISTA
     * false = derecha
     * true = izquierda
     */
    
    switch(state) {
        case 0://QUIETO
            player->setScale(0.5,0.5);
            if(!vista){
                player->setTextureRect(rects[0]);
            }
            if(vista){
                player->setTextureRect(rects[5]);
            }
            break;
        case 1:// ANDANDO DERECHA
            vista = false;
            Derecha();
            break;
        case 2:// ANDANDO IZQUIERDA
            vista = true;
            Izquierda();
            break;
        case 3: //SALTO
                if(!vista){
                    player->setTextureRect(rects[2]);
                }
                else if(vista){
                    player->setTextureRect(rects[7]);
                }
            break;
        case 13: //MIENTRAS SALTA CAMBIA DIRECCION DERECHA
            if(vista){
                vista=false;
                player->setTextureRect(rects[2]);
            }
            break;
        case 23: //MIENTRAS SALTA CAMBIA DIRECCION IZQUIERDA
            if(!vista){
                vista=true;
                player->setTextureRect(rects[7]);
            }
            break;
        case 4: //MUERTE
            player->setTextureRect(rects[4]);
            Muerte();
            break;
        case 5: //DISPARO
            if(arma && bala==NULL){
                    float x,y;
                    if(vista){
                        x = player->getPosition().x;
                        y = player->getPosition().y + player->getGlobalBounds().height/2;
                    }else{
                        x = player->getPosition().x + player->getGlobalBounds().width;
                        y = player->getPosition().y + player->getGlobalBounds().height/2;
                    }
                    bala = new Bullet(x,y,vista,0);
                    bala->update();
                } 
                        
            break;
        case 6: // CAIDA
            if(!vista){
                    player->setTextureRect(rects[1]);
                }
                else{
                    player->setTextureRect(rects[6]);
                }
            break;
        case 7: // REBOOT
            player->setTextureRect(rects[3]);
            break;
            
    }
    if(bala!=NULL && bala->activa()){
        bala->update();
        if(bala->getXPosition()<vistaX || bala->getXPosition()>vistaX+640){
            delete bala;
            bala = NULL;
        }
    }
        
    after = state;
}
void Player::Derecha() {//ANIMACION
    if(clock->getElapsedTime().asSeconds()>0.2){
            player->setTextureRect(rects[0]);
    }
    if(clock->getElapsedTime().asSeconds()>0.4){
            player->setTextureRect(rects[1]);
            clock->restart();
    }
}
void Player::Izquierda() {//ANIMACION
    if(clock->getElapsedTime().asSeconds()>0.2){
            player->setTextureRect(rects[5]);
    }
    if(clock->getElapsedTime().asSeconds()>0.4){
            player->setTextureRect(rects[6]);
            clock->restart();
    }
}
void Player::Muerte(){//ANIMACION
    if(clock->getElapsedTime().asSeconds()>sf::seconds(0.2).asSeconds()) {
        player->setScale(0.5,0.5);
    }
    if(clock->getElapsedTime().asSeconds()>sf::seconds(0.4).asSeconds()) {
        player->setScale(0.4,0.4);
    }
    if(clock->getElapsedTime().asSeconds()>sf::seconds(0.6).asSeconds()) {
        player->setScale(0.3,0.3);
    }
    if(clock->getElapsedTime().asSeconds()>sf::seconds(0.8).asSeconds()) {
        player->setScale(0.5,0.5);
        clock->restart();
    }
}
void Player::setPosition(float x, float y){
    player->setPosition(x,y);
}

sf::FloatRect Player::getGlobalbounds(){
    return player->getGlobalBounds();
}
sf::Vector2f Player::getPosition(){
    return player->getPosition();
}
void Player::movePlayer(sf::Vector2f velocidad){
    player->move(velocidad.x,velocidad.y);
}
sf::Vector2f* Player::getCollisionPoints(){
    return CollisionPoints;
}
void Player::setGun(bool x){
    arma = x; 
}
bool Player::CanYouAGun(){
    return arma;
}
sf::FloatRect Player::getBulletBounds(){
        return bala->getGlobalBounds();
}
bool Player::ActiveBullet(){
    if(bala!=NULL)
        return true;
    return false;
}