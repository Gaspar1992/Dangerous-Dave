#ifndef PUNTUACION_HPP
#define PUNTUACION_HPP

#include "SettingsParser.hpp"
#include "Text.hpp"
#include "sprite.hpp"
#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>

using namespace std;

class Puntuacion : public sf::Drawable{
public:
    Puntuacion(int puntos, int lvl);
    Puntuacion(const Puntuacion& orig);
    void writeName(std::string txt);
    virtual ~Puntuacion();
private:
    SettingsParser * punt;
    Text * text;
    sprite * tablero;
    sprite * nueva;
    ostringstream texto;
    int pos;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        target.draw(*tablero,states);
        if(nueva!=NULL)
            target.draw(*nueva,states);
        if(pos==-1){
            for(int i=0;i<7;i++){
                target.draw(text[i],states);
            }
        }else{
            for(int i=0;i<8;i++){
                target.draw(text[i],states);
            }
        }
    }
};

#endif /* PUNTUACION_HPP */

