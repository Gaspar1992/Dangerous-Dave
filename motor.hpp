#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "window.hpp"
#include <SFML/Window/Event.hpp>
#include "Player.hpp"
#include "Tilemap.hpp"
#include "footer.hpp"
#include "Header.hpp"
#include <iostream>
#include "Text.hpp"
#include "Enemy.hpp"
#include "Puntuacion.hpp"

using namespace std;


class motor {
public:
    motor();
    motor(const motor& orig);
    virtual ~motor();
    
private:
    void update();
    void render();
    void colision();
    void MapaView();
    void updateViews(int x,int y);
    void init();
    void changeLevel();
    void keyboard();
    void reboot();
    //VARIABLES AUXILIARES GENERALES
    int mov,lvl; // ESTADOS PARA EL JUGADOR Y NIVEL ACTUAL (INCLUYENDO LA PANTALLA DE INICIO)
    int vision; // ZONA DE VISION
    //VARIABLES DE MOVIMIENTO
    float movV,movH,gravity,pie;
    //FILTROS DE ESTADO
    bool suelo; // SI HAY SUELO
    bool salto; // SI ESTA SALTANDO
    bool muerte; // SI HA MUERTO
    bool newlvl; // SI SE CAMBIA DE NIVEL
    bool REBOOT; // REINICIO DEL JUEGO AL MORIR Y VER LAS PUNTUACIONES
    bool iniPlayer;
    sf::Vector2f * movimiento; // VECTOR DE MOVIMIENTO
    //VARIABLES DE TIEMPO
    sf::Clock * deadClock; // RELOJ PARA LA MUERTE DEL JUGADOR Y CAMBIO DE NIVEL
    sf::Clock * Tsalto; // PARA EL TIEMPO DE SALTO
    sf::Clock * ia; // RELOJ DE CONTROL PARA LA ACTUALIZACION DE LA IA
    // VARIABLES PARA LA INTERPOLACION
    static const sf::Time IA_TICK_TIME;
    sf::Time timeSinceLastUpdate ;
    float interpolacion;
    //VARIABLE DE EVENTOS
    sf::Event * eventos;
    //VARIABLES DE DIBUJADO
    sf::View * vista; // LA VISTA EN PANTALLA
    Player * jugador; // JUGADPR
    Enemy * enemigo; // ENEMIGOS DEL NIVEL 3
    Tilemap * mapa; // MAPA
    footer * foot; // PIE DE CADA VISTA
    Header * head; // CABEZERA DE CADA VISTA
    Tilemap * transicion; // TRANSICION ENTRE NIVELES E INICIO
    Puntuacion * puntos;
    Text * Txt; // TEXTO TRANSICION
    window * ventana; // VENTANA DEL JUEGO
    float camaramov; //VARIABLE DE VISTA
    float vistaX;
    //VARIABLES AUXILIARES
    //sf::RectangleShape colision1;
    bool trampa;
};

#endif /* MOTOR_HPP */

