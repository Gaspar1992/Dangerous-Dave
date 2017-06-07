#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "tinyxml.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "sprite.hpp"
#include "Player.hpp"

using namespace std;

class Tilemap : public sf::Drawable{
public:
    Tilemap(int level);
    Tilemap(const Tilemap& orig);
    void update();
    virtual ~Tilemap();
    void setActiveLayer(int layer);
    int getWidth();
    int getHeight();
    int getActiveLayer();
    int*** GetColision();
    int*** getTilemap();
    int getTileWidth();
    int getTileHeight();
    sf::Vector2f getTilePosition(int layer,int y, int x);
    sf::FloatRect getTileGlobalBounds(int layer,int y, int x);
    bool removeTile(int layer,int y, int x);
    sf::Vector2f* getInitialPosition();
    bool DoorOpened();
private:
    int _tileWidth,_tileHeight;
    bool door;
    sprite **** _tilemapSprite;
    int ** animaciones, *elemPorAni;
    int ***_tilemap;
    int ***_tileColision;
    int numAnim;
    sf::IntRect *_tilesetSprite;
    sf::Vector2f * initPos;
    sf::Clock * act;
    int _activeLayer,_width,_height,_numLayers;
    void InitialPosition(int level);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
        for(int y=0; y<_height;y++){
            for(int x=0;x<_width;x++){
                if(_tilemapSprite[_activeLayer][y][x]!=NULL)
                    target.draw(*_tilemapSprite[_activeLayer][y][x]);
            }
        }
        //target.draw(*player, states);
    }
    
};

#endif /* TILEMAP_HPP */

