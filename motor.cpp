#include "motor.hpp"

const sf::Time motor::IA_TICK_TIME = sf::seconds(1.f/25.f);


motor::motor() {
    ventana = new window;
    eventos = new sf::Event;
    vista = new sf::View;
    vista->reset(sf::FloatRect(0,0,640,400));
    init(); // INICIALIZA LA VARIABLES
    std::string name;
    while(ventana->isOpen()) {
        
        mov = 0;
        //LIMPIA PANTALLA    
        ventana->clear(sf::Color::Black);
        //ACTUALIZA LA VISTA
        ventana->setView(*vista);
        
        while(ventana->pollEvent(*eventos)) {
            //EVENTO PARA CERRAR LA VENTANA
            if(eventos->type == sf::Event::Closed)
                ventana->close();
            // SI PULSAS CUALQUIER BOTON EN LA PANTALLA DE INICIO
            if(eventos->type == sf::Event::KeyPressed && lvl<1){ 
                lvl++;
                jugador = new Player;
                foot->Game();
                mapa = new Tilemap(lvl);
                head->setLevel(lvl);
                jugador->setPosition(mapa->getInitialPosition()->x,mapa->getInitialPosition()->y);
                delete transicion;
            }//AL CARGAR CADA NIVEL POSICION INICIAL
            if(eventos->type == sf::Event::KeyPressed && lvl>0 && iniPlayer){
                iniPlayer = !iniPlayer;
            }//REINICIO DEL JUEGO
            if(eventos->type == sf::Event::KeyPressed && eventos->key.code==sf::Keyboard::Return && puntos!=NULL){
                reboot();
            }// TRUCO PARA QUE LOS NPCS NI EL ENTORNO NO TE MATEN
            if(eventos->type == sf::Event::KeyPressed && eventos->key.code == sf::Keyboard::A)
                trampa = !trampa;
            // ESCRITURA DEL NOMBRE CUANDO HACES RECORD
            if(eventos->type == sf::Event::TextEntered && puntos!=NULL){
                if(eventos->text.unicode < 128){
                    if(static_cast<char>(eventos->text.unicode)==8){
                        name.pop_back();
                        puntos->writeName(name);
                    }
                    else if(name.length()<3){
                        name += static_cast<char>(eventos->text.unicode);
                        puntos->writeName(name);
                    }
                }
            }
        }//PERMITE LA EJECUCION DE LAS FUNCIONES DESPUES DEL REINICIO
        if(!REBOOT){
            keyboard();
            if(lvl>0 && (puntos!=NULL || !iniPlayer))
                colision();
            MapaView();
            update();
            render();
        }
        ventana->display();
        
    }
}

motor::motor(const motor& orig) {
}

motor::~motor() {
    delete ventana;
    delete eventos;
    delete jugador;
    delete mapa;
    delete foot;
    delete head;
    delete transicion;
    delete puntos;
}

void motor::render(){
    if(!newlvl && lvl>0 && mapa!=NULL){ // NIVELES DE JUEGO
        ventana->draw(*mapa);
        if(lvl==3){
            // POSICION INTERPOLADA
            for(int i=0;i<2;i++){
                if(!enemigo[i].isDead()){
                    enemigo[i].posUpdate(interpolacion);
                    ventana->draw(enemigo[i]);
                }
            }
        }
    }
    else if((newlvl || lvl<1) && puntos==NULL){ // PANTALLA INICIO Y TRANSICIONES
        ventana->draw(*transicion); 
        if(Txt!=NULL) // EL TEXTO EN INICIO ES NULL SOLO APARECE ENTRE TRANSICIONES DE NIVEL
            ventana->draw(*Txt);
    }
    
    
    if(lvl>0 && head->getLives()>0){//SI NO ES LA PANTALLA DE INICIO
        ventana->draw(*jugador);
    }
                      
    
    ventana->draw(*foot);
    if(lvl>0 && head->getLives()==0 && puntos!=NULL){
        ventana->draw(*puntos);
    }
    ventana->draw(*head);
}

void motor::update(){
    if(lvl<1){ // SI ES EL INICIO DEL JUEGO
        transicion->update();
        head->update();
    }else{ // DENTRO DEL JUEGO
        if(iniPlayer)
            mov = 7;
        jugador->update(mov,vistaX);
        if(!newlvl){
            foot->TakeKey(mapa->DoorOpened());
            mapa->update();
            head->update();
            if(ia!=NULL){
                /****************** INTERPOLACION(1) *********************/
                sf::Time elapsedTime = ia->restart();
                timeSinceLastUpdate += elapsedTime;
                while(timeSinceLastUpdate>IA_TICK_TIME){ // TIEMPO DE ACTUALIZACION
                    timeSinceLastUpdate -=IA_TICK_TIME;
                    //ACTUALIZAR
                    for(int i=0;i<2;i++){
                        if(!enemigo[i].isDead())
                            enemigo[i].update(IA_TICK_TIME,vistaX);
                    }
                
                }
                interpolacion = (float) std::min(1.f,timeSinceLastUpdate.asSeconds()/IA_TICK_TIME.asSeconds());
            }
            else if(lvl==3 && ia==NULL){// A PARTIR DEL NIVEL 3 CREAR EL RELOJ DE ACTUALIZACION DE LA IA
                ia = new sf::Clock;
            }
            
            
        }
        else{
            changeLevel();
        }
    }
}
void motor::init(){
    //INICIALIZACION DE LA MAYORIA DE VARIABLES
    iniPlayer = true;
    vistaX = 0;
    camaramov = 15*32;
    timeSinceLastUpdate = sf::Time::Zero;
    trampa = false;
    Txt = NULL;
    foot = new footer;
    head = new Header;
    muerte = false;
    newlvl = false;
    
    /* VARIABLE DE SELECCION DE NIVEL*/
    /*
     * DIFERENTES NIVELES
     * 0 = INICIO
     * 1-3 = NIVELES DE JUEGO
     * 4 = TRANSICION
     * 
     * PD: AL EJECUTAR LOS NIVELES PARA PROBARLOS DIRECTAMENTE NO SE PERMITE
     *      REINICIO DEL JUEGO
     */
    /***********/lvl = 0;/************/
                 
    jugador = new Player;
    foot->PreGame();
    enemigo = NULL;
    mapa = NULL;
    if(lvl>0){
        foot->Game();
        mapa = new Tilemap(lvl);
        head->setLevel(lvl);
        head->setGame(true);
        jugador->setPosition(mapa->getInitialPosition()->x,mapa->getInitialPosition()->y);
        transicion = new Tilemap(4);
        if(lvl==3){
            //enemigo = new Enemy;
            enemigo = new Enemy[2];
            enemigo[0].setPosition(980,135);
            enemigo[1].setPosition(1480,135);
        }
    }
    puntos = NULL;
    transicion = new Tilemap(0);
    vision = 0;
    Tsalto = new sf::Clock;
    gravity = 6.0f;
    movV = 3.8f;
    movH = 3.8f;
    pie = 3.f;
    deadClock = NULL;
    movimiento = new sf::Vector2f(0,0);
    REBOOT = false;
    ia = NULL;
    
}
void motor::colision(){
    if(!muerte){
        suelo = false;
        if(!newlvl){
            if(salto){
                float vy = -movH + gravity*Tsalto->getElapsedTime().asSeconds();
                movimiento->y = vy;  
                if(Tsalto->getElapsedTime().asSeconds()>0.7){
                    Tsalto->restart();
                    salto = false;
                }
            }
            switch(mov){
                case 1://DERECHA
                        movimiento->x=pie;
                    break;
                case 2://IZQUIERDA
                        movimiento->x=-pie;
                    break;
                case 3://SALTO QUIETO
                    if(!salto){
                        Tsalto->restart();
                    }
                    break;
                case 13://SALTO+DERECHA
                    if(!salto){
                        Tsalto->restart();
                    }
                    movimiento->x=pie*2;
                    break;
                case 23://SALTO+IZQUIERDA
                    if(!salto){
                        Tsalto->restart();
                    }
                    movimiento->x=-pie*2;
                    break;
                default:
                    movimiento->x=0.f;
                    break;
            }
            for(int y=0;y<mapa->getHeight();y++){
                for(int x=0;x<mapa->getWidth();x++){
                    
                    /* MAPA DE COLISION, TIPOS DE BLOQUE
                     * mapa->GetColision()[mapa->getActiveLayer()][y][x]
                     * 0 = TRASPASABLES
                     * 1 = COLISION
                     * 2 = OBJETOS
                     * 3 = OBJETOS QUE MATAN AL JUGADOR
                     * 4 = LA PUERTA
                     */
                    //PUERTA ABIERTA
                    if(mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).intersects(jugador->getGlobalbounds())){
                        // PUERTA
                        if(mapa->GetColision()[mapa->getActiveLayer()][y][x]==4){
                            //PUERTA ABIERTA
                            if(mapa->DoorOpened())
                                newlvl = true; // CAMBIO DE NIVEL
                        }
                        else if(mapa->GetColision()[mapa->getActiveLayer()][y][x]==1){
                            //MURO DERECHO
                            if(mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[2].x+10,jugador->getPosition().y+jugador->getCollisionPoints()[2].y+6) ||
                        mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[4].x+10,jugador->getPosition().y+jugador->getCollisionPoints()[4].y) ||
                        mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[7].x+10,jugador->getPosition().y+jugador->getCollisionPoints()[7].y-7.f)){
                                if(movimiento->x > 0)
                                    movimiento->x = 0.f;
                            }
                            //MURO IZQUIERDO
                            else if(mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[0].x-1,jugador->getPosition().y+jugador->getCollisionPoints()[0].y+6) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[3].x-1,jugador->getPosition().y+jugador->getCollisionPoints()[3].y) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[5].x-1,jugador->getPosition().y+jugador->getCollisionPoints()[5].y-7.f)){
                                if(movimiento->x < 0)
                                    movimiento->x = 0.f;
                            }
                            //SUELO
                            else if(jugador->getPosition().y+jugador->getGlobalbounds().height-5<=mapa->getTilePosition(mapa->getActiveLayer(),y,x).y && movimiento->y>=0 && (mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[5].x+7,jugador->getPosition().y+jugador->getCollisionPoints()[5].y+2.5f) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[6].x,jugador->getPosition().y+jugador->getCollisionPoints()[6].y+2.5f) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[7].x-7,jugador->getPosition().y+jugador->getCollisionPoints()[7].y+2.5f) 
                                    )){
                                suelo = true;
                                movimiento->y=0.f;
                            }
                            
                            //TECHO
                            else if(mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[1].x,jugador->getPosition().y+jugador->getCollisionPoints()[1].y+1) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[0].x+8,jugador->getPosition().y+jugador->getCollisionPoints()[0].y+1) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[2].x-8,jugador->getPosition().y+jugador->getCollisionPoints()[2].y+1)){
                                    movimiento->y = 0.f;
                                    salto = false;
                            }
                        }
                        //OBJETOS Y SUS DIFERENTES PUNTUACIONES
                        else if(mapa->GetColision()[mapa->getActiveLayer()][y][x]==2){

                            if(mapa->getTilemap()[mapa->getActiveLayer()][y][x]==31)
                                head->setPoints(+100);
                            else if(mapa->getTilemap()[mapa->getActiveLayer()][y][x]==32)
                                head->setPoints(+200);
                            else if(mapa->getTilemap()[mapa->getActiveLayer()][y][x]==35)
                                head->setPoints(+50);
                            else if(mapa->getTilemap()[mapa->getActiveLayer()][y][x]==21){
                                foot->TakeGun(true);jugador->setGun(true);
                            }
                            mapa->removeTile(mapa->getActiveLayer(),y,x);
                        }
                        //TILES QUE PUEDEN ELIMINARTE
                        else if(mapa->GetColision()[mapa->getActiveLayer()][y][x]==3 && (
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[3].x+1,jugador->getPosition().y+jugador->getCollisionPoints()[3].y) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[4].x-1,jugador->getPosition().y+jugador->getCollisionPoints()[4].y) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[5].x+1,jugador->getPosition().y+jugador->getCollisionPoints()[5].y-3) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[6].x,jugador->getPosition().y+jugador->getCollisionPoints()[6].y-1) ||
                            mapa->getTileGlobalBounds(mapa->getActiveLayer(),y,x).contains(jugador->getPosition().x+jugador->getCollisionPoints()[7].x-1,jugador->getPosition().y+jugador->getCollisionPoints()[67].y-3)
                            ) && !trampa){
                            muerte=true;
                            salto=false;
                            movimiento->x=0;
                            movimiento->y=0;
                            deadClock = new sf::Clock;
                        }
                    }
                }
            }
            //COLISIONES CON LOS NPCS
            if(!muerte && enemigo!=NULL){
                for(int i=0;i<2;i++){
                    //CHOQUE JUGADOR && NPC
                    if(enemigo[i].getGlobalBounds().intersects(jugador->getGlobalbounds()) && !trampa){
                        muerte=true;
                        salto=false;
                        movimiento->x=0;
                        movimiento->y=0;
                        deadClock = new sf::Clock;
                        enemigo[i].Dead();
                    }
                    //CHOQUE ATAQUE JUGADOR CONTRA NPC
                    else if(jugador->CanYouAGun() && jugador->ActiveBullet() && enemigo[i].getGlobalBounds().intersects(jugador->getBulletBounds()))
                        enemigo[i].Dead();
                    //CHOQUE ATAQUE NPC CONTRA JUGADOR
                    else if(enemigo[i].ActiveBullet() && enemigo[i].getBulletBounds().intersects(jugador->getGlobalbounds()) && !trampa){
                        muerte=true;
                        salto=false;
                        movimiento->x=0;
                        movimiento->y=0;
                        deadClock = new sf::Clock;
                    }
                }
            }
            //DIFERENTES ESTADOS DE ANIMACIONES PARA EL JUGADOR Y GRAVEDAD
            if(salto && mov==35)
                mov = 5;
            else if(!suelo && !salto){
                movimiento->y = gravity/2;
                mov=6;
            }
            else if(suelo && !salto && (mov==3 || mov==13 || mov==23))
                salto=true;
            else if(mov==1 && salto)//DERECHA
                mov=13;
            else if(mov==2 && salto)//IZQUIERDA
                mov=23;
            else if(salto)
                mov=3;
            
        }else{
            mov = 1;
            movimiento->x = pie;
        }
    }
    else if(muerte){
        movimiento->x=0;
        movimiento->y=0;
        mov=4;
        if(deadClock->getElapsedTime().asSeconds()>2){
            jugador->setPosition(mapa->getInitialPosition()->x,mapa->getInitialPosition()->y);
            delete deadClock;
            deadClock = NULL;
            head->setLives(-1);
            mov = 0;
            muerte = false;
            if(head->getLives()==0){
                puntos = new Puntuacion(head->getPoints(),lvl);
            }
        }
    }
    jugador->movePlayer(*movimiento);
}
void motor::MapaView(){
    if(!newlvl){
        //VALORO LAS DIFERENTES POSICIONES DEL JUGADOR PARA MOVER LA CAMARA
        if(jugador->getPosition().x>18*32 && vision==0){
            updateViews(camaramov,0);
            vistaX +=camaramov;
            vision++;
        }else if(jugador->getPosition().x<17*32 && vision==1){
            updateViews(-camaramov,0);
            vistaX +=-camaramov;
            vision--;
        }else if(jugador->getPosition().x > 33*32 && vision==1){
            updateViews(camaramov,0);
            vistaX +=camaramov;
            vision++;
        }else if(jugador->getPosition().x < 31*32 && vision==2){
            updateViews(-camaramov,0);
            vistaX +=-camaramov;
            vision--;
        }else if(jugador->getPosition().x > 48*32 && vision==2){
            updateViews(camaramov,0);
            vistaX +=camaramov;
            vision++;
        }else if(jugador->getPosition().x < 47*32 && vision==3){
            updateViews(-camaramov,0);
            vistaX +=-camaramov;
            vision--;
        }else if(jugador->getPosition().x > 63*32 && vision==3){
            updateViews(camaramov,0);
            vistaX +=camaramov;
            vision++;
        }else if(jugador->getPosition().x < 62*32 && vision==4){
            updateViews(-camaramov,0);
            vistaX +=-camaramov;
            vision--;
        }
        
    }else if(newlvl){
        updateViews(-camaramov*vision,0);
    }
}
void motor::updateViews(int x,int y){
    head->move(x,y);
    foot->move(x,y);
    if(newlvl)
        vista->reset(sf::FloatRect(0,0,640,400));
    else
        vista->move(x,y);
}
void motor::changeLevel(){
    if(deadClock==NULL){
        // CREAR LA TRANSICION Y EL RELOJ QUE LIMITA EL TIEMPO DE LA MISMA
        // TODO LO QUE SE MUESTRA
        transicion = new Tilemap(4);
        Txt = new Text;
        Txt->setColor(sf::Color::White);
        Txt->setFont("Arial.ttf");
        Txt->setSize(20);
        Txt->setPosition(160,110);
        // SU TIEMPO DE MUESTRA
        deadClock = new sf::Clock;
        foot->TakeGun(false);
        foot->TakeKey(false);
        //REINICIA LA VISTA
        vision=0;
        vistaX = 0;
        //COLOCA AL JUGADOR EN LA TRANSICION
        jugador->setPosition(transicion->getInitialPosition()->x,transicion->getInitialPosition()->y);
        //BORRA EL MAPA
        delete mapa;
        // SIGUIENTE NIVEL
        lvl++;
        if(lvl==3){
            enemigo = new Enemy[2];
            enemigo[0].setPosition(980,135);
            enemigo[1].setPosition(1480,135);
        }
    }
    else if(deadClock->getElapsedTime().asSeconds()<4.f){
        // DURANTE LA TRANSICION
        std::ostringstream ss; // VARIABLE DE TEXTO
        ss << "GOOD WORK! ONLY " << 11-lvl << " MORE TO GO"; 
        Txt->setString(ss.str());
        
        mov = 1; // MANDO ESTE ESTADO PARA QUE EL JUGADOR ANDE AUTOMATICAMENTE
        
        // CARGO EL MAPA UN POCO ANTES
        if(deadClock->getElapsedTime().asSeconds()>3.5f){
            mapa = new Tilemap(lvl);
        }
    }
    
    else if(deadClock->getElapsedTime().asSeconds()>4.f){
        // FINAL DE LA TRANSICION ELIMINO Y ACTUALIZO CLASES
        delete deadClock; deadClock = NULL;
        jugador->setPosition(mapa->getInitialPosition()->x,mapa->getInitialPosition()->y);
        head->setLevel(lvl);
        newlvl=false;
        delete transicion;
        delete Txt; Txt=NULL;
            
    }
    
}
void motor::keyboard(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        mov = 1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        mov = 2;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && suelo && lvl>0)
        mov = 3;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && suelo)
        mov = 13;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && suelo)
        mov = 23;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && jugador->CanYouAGun())
        mov = 5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && jugador->CanYouAGun() && salto)
        mov = 35;
}
void motor::reboot(){
    REBOOT = true;
    delete head;
    delete foot;
    delete puntos;
    delete jugador;
    delete movimiento;
    delete Tsalto;
    delete mapa;
    init();
}
