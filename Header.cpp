#include "Header.hpp"

Header::Header() {
    game = false;
    Puntos = 0;
    level = 0;
    headText = new Text[3];
    //TEXTO DE LA CABECERA
    for(int i=0;i<3;i++){
        headText[i].setColor(sf::Color::Green);
        headText[i].setFont("Arial.ttf");
        headText[i].setSize(26);
        if(i==0){
            texto << "SCORE:  " <<setfill('0')<< setw(5) << Puntos ;
            headText[i].setPosition(0,0);
        }
        if(i==1){
            if(level<1){
                texto << "      BY JOHN ROMERO \n (C) 1990 SOFTDISK. INC";
                headText[i].setSize(16);
                headText[i].setPosition(220,90);
                headText[i].setColor(sf::Color::White);
            }
        }
        if(i==2){
            texto << "  DAVES:";
            headText[i].setPosition(400,0);
        }
        headText[i].setString(texto.str());
        texto.str("");
    }
    
    
    
    
}

Header::Header(const Header& orig) {
}

Header::~Header() {
    delete[] headText;
    delete head;
    delete[] lives;
}
void Header::setLevel(int lvl){
    level = lvl;
}
void Header::setPoints(int Points){
    Puntos +=Points;
}
int Header::getLives(){
    return Nlives;
}
int Header::getPoints(){
    return Puntos;
}
void Header::move(float x, float y){
    head->move(x,y);
    for(int i=0;i<3;i++){
        headText[i].move(x,y);
    }
    for(int i=0;i<Nlives-1;i++){
        lives[i].move(x,y);
        
    }
}
void Header::setGame(bool g){
    game = g;
}
void Header::update(){
    if(level<1){//PANTALLA DE INICIO
        if(game){
            updateTitle();
        }else{
            title = new sprite;
            title->setTexture("1.png");
            title->setPosition(200,-10);
            reloj = new sf::Clock;
            game = true;
        }
        
    }else{//PANTALLAS DEL JUEGO
        if(game){//SOLO UNA VEZ
            delete title;
            title=NULL;
            delete reloj;
            headText[1].setColor(sf::Color::Green);
            headText[1].setSize(26);
            headText[1].setPosition(200,0);
            head = new sprite;
            head->setTexture("footer.png");
            head->setOrigin(head->getGlobalBounds().width/2,head->getGlobalBounds().height/2);
            head->rotate(180);
            head->setPosition(head->getGlobalBounds().width/2,16);
            Nlives = 4;
            lives = new sprite[Nlives-1];
            for(int i=0;i<Nlives-1;i++){
                lives[i].setTexture("lifes.png");
                lives[i].scale(2,2);
                lives[i].setPosition(510+32*i,3);
            }
            game = false;
        }//ACTUALIZAR INFORMACION
        for(int i=0;i<3;i++){
            if(i==0){
                texto << "SCORE:  " <<setfill('0')<< setw(5) << Puntos ;
            }
            if(i==1){
                
                texto << "  LEVEL  " <<setfill('0')<< setw(2) <<level;
            }
            if(i==2){
                texto << "  DAVES:";
            }
            headText[i].setString(texto.str());
            texto.str("");
        }
    }
}
void Header::setLives(int live){
    Nlives += live;
}
void Header::updateTitle(){//ANIMACION
    if(reloj->getElapsedTime().asSeconds()>0.2)
            title->setTexture("2.png");
    if(reloj->getElapsedTime().asSeconds()>0.4)
        title->setTexture("3.png");
    if(reloj->getElapsedTime().asSeconds()>0.6){
        title->setTexture("1.png");
        reloj->restart();
    }
}