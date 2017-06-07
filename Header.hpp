#ifndef HEADER_HPP
#define HEADER_HPP

#include "sprite.hpp"
#include "Text.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

class Header : public sf::Drawable{
public:
    Header();
    Header(const Header& orig);
    virtual ~Header();
    void setLevel(int lvl);
    void setPoints(int Points);
    int getPoints();
    int getLives();
    void move(float x, float y);
    void setGame(bool g);
    void update();
    void setLives(int live);
    void updateTitle();
private:
    sprite * head;
    sprite * lives;
    sprite * title;
    bool game;
    Text * headText;
    sf::Clock * reloj;
    int Nlives, Puntos , level;
    ostringstream texto;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        if(level<1){
            target.draw(*title, states);
            target.draw(headText[1],states);
        }
        else{
            target.draw(*head, states);
            for(int i=0;i<3;i++){
                target.draw(headText[i], states);
            }

            if(Nlives>1){
                for(int i=0;i<Nlives-1;i++){
                    target.draw(lives[i], states);
                }
            }
        }
    }
};

#endif /* HEADER_HPP */

