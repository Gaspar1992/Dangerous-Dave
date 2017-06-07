#include "footer.hpp"

footer::footer() {
    Footer = new sprite;
    Footer->setPosition(0,330);
    Footer->setTexture("footer1.png");
    pregame = true;
    gun = NULL;
    door = NULL;
    text = new Text;
    text->setColor(sf::Color::White);
    text->setFont("Arial.ttf");
    text->setSize(18);
    text->setString("PRESS THE F1 KEY FOR HELP");
    text->setPosition(200,340);
}

footer::footer(const footer& orig) {
}

footer::~footer() {
    delete Footer;
}

void footer::move(int x, int y){
    //MOVER TODOS LOS OBJETOS
    Footer->move(x,y);
    if(gun!=NULL)
        gun->move(x,y);
    if(door!=NULL)
        door->move(x,y);
}
void footer::TakeGun(bool x){
    //ACTIVAR/DESACTIVAR ARMA
    if(gun==NULL && x){
        gun = new sprite;
        gun->setTexture("gun.png");
        gun->setPosition(500,345);
    }else if(!x && gun!=NULL){
        delete gun;gun = NULL;
    }
    
}
void footer::TakeKey(bool x){
    //ACTIVAR/DESACTIVAR LLAVE
    if(x && door==NULL){
        door = new sprite;
        door->setTexture("door.png");
        door->setPosition(130,370);
    }else if(!x && door!=NULL){
        delete door;door = NULL;
    }
}
void footer::Game(){
    Footer->setTexture("footer.png");
    text->setString("");
}
void footer::PreGame(){
    Footer->setTexture("footer1.png");
    text->setString("PRESS THE F1 KEY FOR HELP");
    if(door!=NULL)
        delete door;
    if(gun!=NULL)
        delete gun;
    door = NULL;
    gun = NULL;
}