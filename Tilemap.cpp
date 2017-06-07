#include "Tilemap.hpp"

Tilemap::Tilemap(int level) {
    _activeLayer =0;
    door = false;
    TiXmlDocument doc;
    switch(level){
        case 0:
            doc.LoadFile("resources/inicio.tmx");
            break;
        case 1:
            doc.LoadFile("resources/lvl1.tmx");
            break;
        case 2:
            doc.LoadFile("resources/lvl2.tmx");
            break;
        case 3:
            doc.LoadFile("resources/lvl3.tmx");
            break;
        case 4:
            doc.LoadFile("resources/transicion.tmx");
            break;
    }
    int _tilecount,_rows,_columns;
    _numLayers = 0;
    InitialPosition(level);
    //Tamaño del mapa y de los tiles
    TiXmlElement * map = doc.FirstChildElement("map");
    
    //CARGA DE LAS ANIMACIONES
    numAnim = 0;
    TiXmlElement * tileset= map->FirstChildElement("tileset");
    TiXmlElement * animTiles = tileset->FirstChildElement("tile");
    //NUMERO DE ANIMACIONES
    while(animTiles){
        numAnim++;
        animTiles = animTiles->NextSiblingElement("tile");
    }
    int elementos = 0; // NUMERO DE SPRITES DE LA ANIMACION
    animTiles = tileset->FirstChildElement("tile");
    animaciones = new int*[numAnim];
    elemPorAni = new int[numAnim];
    int * aux = new int[10];
    //CARGA 
    for(int i=0;i<numAnim;i++){
        TiXmlElement * frames = animTiles->FirstChildElement("animation")->FirstChildElement("frame");
        while(frames){
            frames->QueryIntAttribute("tileid",&aux[elementos]);
            elementos++;
            frames = frames->NextSiblingElement("frame");
        }
        elemPorAni[i] = elementos;
        animaciones[i] = new int[elementos];
        for(int e=0;e<elementos;e++){
            animaciones[i][e]=aux[e];
        }
        elementos=0;
        animTiles = animTiles->NextSiblingElement("tile");
        
    }
    
    //CARGA DE VARIABLES
    map->QueryIntAttribute("width",&_width);
    map->QueryIntAttribute("height",&_height);
    map->QueryIntAttribute("tilewidth",&_tileWidth);
    map->QueryIntAttribute("tileheight",&_tileHeight);
    map->FirstChildElement("tileset")->QueryIntAttribute("tilecount",&_tilecount);
    map->FirstChildElement("tileset")->QueryIntAttribute("columns",&_columns);
    _rows = _tilecount/_columns;
    
    //VARIABLE ARBITRARIA, MISMO TILESET PARA TODOS LOS MAPAS
    string filename = "tileset.png";
    
    //CARGA DEL MAPA (SIMILIAR APUNTES)
    TiXmlElement * layer = map->FirstChildElement("layer");
    while(layer){
        _numLayers++;
        layer = layer->NextSiblingElement("layer");
    }
    _tilesetSprite = new sf::IntRect[_tilecount];
    for(int y=0;y<_rows;y++){
        for(int x=0;x<_columns;x++){
            _tilesetSprite[x+y*5] = sf::IntRect(x*32,y*32,_tileWidth,_tileHeight);
        }
    }
    
    _tilemap = new int**[_numLayers];
    _tileColision = new int**[_numLayers];
    for(int i=0;i<_numLayers;i++){
        _tilemap[i] = new int*[_height];
        _tileColision[i] = new int*[_height];
    }
    for(int l=0;l<_numLayers;l++){
        for(int y=0;y<_height;y++){
            _tilemap[l][y] = new int[_width];
            _tileColision[l][y] = new int[_width];
        }
    }
    TiXmlElement * data[_numLayers];
    data[0] = map->FirstChildElement("layer")->FirstChildElement("data")->FirstChildElement("tile");
    
    for(int l=0;l<_numLayers; l++){
        for(int y=0; y<_height; y++){
            for(int x=0;x<_width;x++){
                data[l]->QueryIntAttribute("gid", &_tilemap[l][y][x]);
                if(_tilemap[l][y][x]==2||_tilemap[l][y][x]==6 ||_tilemap[l][y][x]==16 ||_tilemap[l][y][x]==17 ||_tilemap[l][y][x]==18 ||_tilemap[l][y][x]==19 ||_tilemap[l][y][x]==20 || _tilemap[l][y][x]==30){
                    _tileColision[l][y][x]=1; //NO PUEDE ATRAVESAR
                }else if(_tilemap[l][y][x]==5 || _tilemap[l][y][x]==11 || _tilemap[l][y][x]==12 || _tilemap[l][y][x]==13 ||_tilemap[l][y][x]==14 || _tilemap[l][y][x]==15 || _tilemap[l][y][x]==21 || _tilemap[l][y][x]==31 || _tilemap[l][y][x]==32 || _tilemap[l][y][x]==35){
                    _tileColision[l][y][x]=2; //PUEDE OBTENER
                }else if(_tilemap[l][y][x]==7 || _tilemap[l][y][x]==8 ||_tilemap[l][y][x]==9 || _tilemap[l][y][x]==10 || _tilemap[l][y][x]==26 || _tilemap[l][y][x]==27 || _tilemap[l][y][x]==28 || _tilemap[l][y][x]==29 || _tilemap[l][y][x]==34 ||_tilemap[l][y][x]==33){
                    _tileColision[l][y][x]=3; //PUEDE MATARLE
                }else if(_tilemap[l][y][x]==3)
                    _tileColision[l][y][x]=4; // PUERTA
                else
                    _tileColision[l][y][x]=0; //NINGUNA INTERACCION
                //Avanzo al siguiente tag
                data[l] = data[l]->NextSiblingElement("tile");
            }
        }
    }
    
    _tilemapSprite = new sprite***[_numLayers];
    for(int l=0;l<_numLayers;l++){
       _tilemapSprite[l] = new sprite** [_height];
    }
    for(int l=0;l<_numLayers;l++){
        for(int y=0;y<_height;y++){
            _tilemapSprite[l][y] = new sprite*[_width];
            for(int x=0;x<_width;x++){
                int gid = _tilemap[l][y][x]-1;
                if(gid>=_rows*_columns){
                    cout << "Error, gid at (l,x,y) = (" << l << "," << x << "," << "y" << ") :" << gid << "fuera del rango del tileset (" << _rows*_columns << ")" << endl;
                }else if(gid>0){
                    //Si fuera 0 no creo sprite
                    
                    _tilemapSprite[l][y][x] = new sprite;
                    _tilemapSprite[l][y][x]->setTexture(filename);
                    _tilemapSprite[l][y][x]->setTextureRect(_tilesetSprite[gid]);
                    _tilemapSprite[l][y][x]->setPosition(x*_tileWidth,35+y*_tileHeight);
                    if(gid==16)
                        _tilemapSprite[l][y][x]->setColor(sf::Color::Transparent);
                }else{
                    _tilemapSprite[l][y][x]= NULL;
                }
            }
        }
    }
    act = new sf::Clock;
}

Tilemap::Tilemap(const Tilemap& orig) {
}

Tilemap::~Tilemap() {
    delete   initPos;
    delete   act;
    for(int i=0;i<numAnim;i++){
        delete[] animaciones[i];
    }
    delete[] animaciones;
    delete[] _tilesetSprite;
    delete[] elemPorAni;
    
    for(int l=0;l<_numLayers;l++){
        for(int y=0;y<_height;y++){
            delete[] _tilemap[l][y];
            delete[] _tileColision[l][y];
            delete[] _tilemapSprite[l][y];
        }
        delete[] _tilemap[l];
        delete[] _tileColision[l];
        delete[] _tilemapSprite[l];
    }
    delete[] _tilemap;
    delete[] _tileColision;
    delete[] _tilemapSprite;
    
    
}

void Tilemap::setActiveLayer(int layer){
    _activeLayer = layer;
}
int Tilemap::getActiveLayer(){
    return _activeLayer;
}
int Tilemap::getHeight(){
    return _height;
}
int Tilemap::getWidth(){
    return _width;
}

void Tilemap::update() {
    //FILTRO DE TIEMPO DE ACTUALIZACION
    if(act->getElapsedTime().asSeconds()>0.2){
        //BUSCA DENTRO DE LA CAPA ACTIVA
        for(int y=0;y<_height;y++){
            for(int x=0;x<_width;x++){
                //CODIGO GID DEL TILE
                int gid = _tilemap[_activeLayer][y][x]-1;
                //VARIABLE AUX
                int d=-1;
                // COMPARAR CON LAS ANIMACIONES
                for(int a=0;a<numAnim;a++){
                    //CADA ELEMENTO DE LA ANIMACIONES
                    for(int f=0;f<elemPorAni[a];f++){
                        //SI COINCIDE CON GID DE LAS ANIMACIONES
                        if(gid==animaciones[a][f] && d==-1){
                            //SI EL ELEMENTO ES FINAL ACTUALIZA AL PRIMERO
                            d++;
                            if(f+1<elemPorAni[a]){
                                _tilemap[_activeLayer][y][x] = animaciones[a][f+1]+1;
                                _tilemapSprite[_activeLayer][y][x]->setTextureRect(_tilesetSprite[animaciones[a][f+1]]);
                                
                            }else{
                                _tilemap[_activeLayer][y][x] = animaciones[a][0]+1;
                                _tilemapSprite[_activeLayer][y][x]->setTextureRect(_tilesetSprite[animaciones[a][0]]);
                            }
                        }
                        
                    }

                }
            }
        }
        act->restart();
    }
}

int*** Tilemap::GetColision(){
    return _tileColision;
}
int Tilemap::getTileHeight(){
    return _tileHeight;
}
int Tilemap::getTileWidth(){
    return _tileWidth;
}
sf::FloatRect Tilemap::getTileGlobalBounds(int layer, int y, int x){
    if(_tilemapSprite[layer][y][x]==NULL)
        return sf::FloatRect(0,0,0,0);
    return _tilemapSprite[layer][y][x]->getGlobalBounds();
}
bool Tilemap::removeTile(int layer, int y, int x){
    //BORRAR ELEMENTOS DEL MAPA
    if(_tilemapSprite[layer][y][x]==NULL)
        return false;
    else if(_tilemap[layer][y][x]==11 || _tilemap[layer][y][x]==12 ||_tilemap[layer][y][x]==13 ||_tilemap[layer][y][x]==14 ||_tilemap[layer][y][x]==15)
        door=true;
    _tilemapSprite[layer][y][x]=NULL;
    _tilemap[layer][y][x]=0;
    return true;
}

void Tilemap::InitialPosition(int level){
    //POSICIONES INICIALES DEL JUGADOR A CADA MAPA
    initPos = new sf::Vector2f;
    switch(level){
        case 0:
            *initPos = sf::Vector2f(-32,-32);
            break;
        case 1:
            *initPos = sf::Vector2f(64,291);
            break;
        case 2:
            *initPos = sf::Vector2f(32,291);
            break;
        case 3:
            *initPos = sf::Vector2f(64,195);
            break;
        case 4:
            *initPos = sf::Vector2f(32,163);
            break;
    }
}
sf::Vector2f* Tilemap::getInitialPosition(){
    return initPos;
}
int*** Tilemap::getTilemap(){
    return _tilemap;
}
bool Tilemap::DoorOpened(){
    return door;
}
sf::Vector2f Tilemap::getTilePosition(int layer, int y, int x){
    if(_tilemapSprite[layer][y][x]==NULL)
        return sf::Vector2f(0,0);
    return _tilemapSprite[layer][y][x]->getPosition();
}