#include "Puntuacion.hpp"

Puntuacion::Puntuacion(int puntos, int lvl) {
    //CONSTRUCCION DE LA CLASE
    punt = new SettingsParser;
    punt->loadFromFile("resources/puntuacion.txt");
    tablero = new sprite;
    tablero->setTexture("tablon.png");
    tablero->setPosition(100,80);
    int comp = 0;
    pos=-1;
    //COMPARA PUNTUACIONES
    for(int i=0;i<5;i++){
        if(i==0){
            punt->get("1Punt",comp);
            if(comp<puntos && pos==-1)
                pos=0;
        }
        if(i==1){
            punt->get("2Punt",comp);
            if(comp<puntos && pos==-1)
                pos=1;
        }
        if(i==2){
            punt->get("3Punt",comp);
            if(comp<puntos && pos==-1)
                pos=2;
        }
        if(i==3){
            punt->get("4Punt",comp);
            if(comp<puntos && pos==-1)
                pos=3;
        }
        if(i==4){
            punt->get("5Punt",comp);
            if(comp<puntos && pos==-1)
                pos=4;
        }
    }
    //SI TIENE PUESTO
    if(pos!=-1){
        text = new Text[8];
        nueva = new sprite;
        nueva->setTexture("high.png");
        nueva->setPosition(0,350);
        for(int i=5;i>pos;i--){
            int aux0=0;
            std::string aux1="";
            if(i==5){
                if(pos==4){
                    punt->set("5Name","\t  ");
                    punt->set("5Punt",puntos);
                    punt->set("5Lvel",lvl);
                }
                else{
                    punt->get("4Punt",aux0);
                    punt->set("5Punt",aux0);
                    punt->get("4Name",aux1);
                    punt->set("5Name",aux1);
                    punt->get("4Lvel",aux0);
                    punt->set("5Lvel",aux0); 
                }
            }
            if(i==4){
                if(pos==3){
                    punt->set("4Name","\t  ");
                    punt->set("4Punt",puntos);
                    punt->set("4Lvel",lvl);
                }
                else{
                    punt->get("3Punt",aux0);
                    punt->set("4Punt",aux0);
                    punt->get("3Name",aux1);
                    punt->set("4Name",aux1);
                    punt->get("3Lvel",aux0);
                    punt->set("4Lvel",aux0);
                }
            }
            if(i==3){
                if(pos==2){
                    punt->set("3Name","\t  ");
                    punt->set("3Punt",puntos);
                    punt->set("3Lvel",lvl);
                }
                else{
                    punt->get("2Punt",aux0);
                    punt->set("3Punt",aux0);
                    punt->get("2Name",aux1);
                    punt->set("3Name",aux1);
                    punt->get("2Lvel",aux1);
                    punt->set("3Lvel",aux1);
                }
            }
            if(i==2){
                if(pos==1){
                    punt->set("2Name","\t  ");
                    punt->set("2Punt",puntos);
                    punt->set("2Lvel",lvl);
                }
                else{
                    punt->get("1Punt",aux0);
                    punt->set("2Punt",aux0);
                    punt->get("1Name",aux1);
                    punt->set("2Name",aux1);
                    punt->get("1Lvel",aux1);
                    punt->set("2Lvel",aux1);
                }
            }
            if(i==1){
                punt->set("1Name","\t  ");
                punt->set("1Punt",puntos);
                punt->set("1Lvel",lvl);
            }
            for(int i=0;i<8;i++){
                int aux0,aux2;
                std::string aux1;
                text[i].setFont("Arial.ttf");
                text[i].setSize(18);
                text[i].setColor(sf::Color::Black);
                if(i==0){
                    text[i].setSize(20);
                    text[i].setString("HIGH SCORES");
                    text[i].setPosition(245,90);
                }
                if(i==1){
                    text[i].setSize(18);
                    text[i].setString("SCORE                NAME                LEVEL");
                    text[i].setPosition(150,140);
                    text[i].setstyle(sf::Text::Underlined);
                }
                if(i==2){
                    punt->get("1Punt",aux0);
                    punt->get("1Name",aux1);
                    punt->get("1Lvel",aux2);
                    texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                    text[i].setString(texto.str());texto.str("");
                    text[i].setPosition(160,130+20*i);
                }
                if(i==3){
                    punt->get("2Punt",aux0);
                    punt->get("2Name",aux1);
                    punt->get("2Lvel",aux2);
                    texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                    text[i].setString(texto.str());texto.str("");
                    text[i].setPosition(160,130+20*i);

                }
                if(i==4){
                    punt->get("3Punt",aux0);
                    punt->get("3Name",aux1);
                    punt->get("3Lvel",aux2);
                    texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                    text[i].setString(texto.str());texto.str("");
                    text[i].setPosition(160,130+20*i);
                }
                if(i==5){
                    punt->get("4Punt",aux0);
                    punt->get("4Name",aux1);
                    punt->get("4Lvel",aux2);
                    texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                    text[i].setString(texto.str());texto.str("");
                    text[i].setPosition(160,130+20*i);
                }
                if(i==6){
                    punt->get("5Punt",aux0);
                    punt->get("5Name",aux1);
                    punt->get("5Lvel",aux2);
                    texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                    text[i].setString(texto.str());texto.str("");
                    text[i].setPosition(160,130+20*i);
                }
                if(i==7 && pos!=-1){
                    text[i].setFont("Arial.ttf");
                    text[i].setSize(18);
                    text[i].setColor(sf::Color::Black);
                    text[i].setPosition(295,130+20*(pos+2));
                }
            }
        }
    }else{
        //SI NO TIENE PUESTO
        text = new Text[7];
        nueva = NULL;
        for(int i=0;i<7;i++){
            int aux0,aux2;
            std::string aux1;
            text[i].setFont("Arial.ttf");
            text[i].setSize(18);
            text[i].setColor(sf::Color::Black);
            if(i==0){
                text[i].setSize(20);
                text[i].setString("HIGH SCORES");
                text[i].setPosition(245,90);
            }
            if(i==1){
                text[i].setSize(18);
                text[i].setString("SCORE                NAME                LEVEL");
                text[i].setPosition(150,140);
                text[i].setstyle(sf::Text::Underlined);
            }
            if(i==2){
                punt->get("1Punt",aux0);
                punt->get("1Name",aux1);
                punt->get("1Lvel",aux2);
                texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                text[i].setString(texto.str());texto.str("");
                text[i].setPosition(160,130+20*i);
            }
            if(i==3){
                punt->get("2Punt",aux0);
                punt->get("2Name",aux1);
                punt->get("2Lvel",aux2);
                texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                text[i].setString(texto.str());texto.str("");
                text[i].setPosition(160,130+20*i);

            }
            if(i==4){
                punt->get("3Punt",aux0);
                punt->get("3Name",aux1);
                punt->get("3Lvel",aux2);
                texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                text[i].setString(texto.str());texto.str("");
                text[i].setPosition(160,130+20*i);
            }
            if(i==5){
                punt->get("4Punt",aux0);
                punt->get("4Name",aux1);
                punt->get("4Lvel",aux2);
                texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                text[i].setString(texto.str());texto.str("");
                text[i].setPosition(160,130+20*i);
            }
            if(i==6){
                punt->get("5Punt",aux0);
                punt->get("5Name",aux1);
                punt->get("5Lvel",aux2);
                texto <<setfill('0')<< setw(5)<< aux0 << "\t\t\t\t " << aux1 << "\t\t\t\t\t\t" << aux2;
                text[i].setString(texto.str());texto.str("");
                text[i].setPosition(160,130+20*i);
            }
            if(i==7 && pos!=-1){
                text[i].setFont("Arial.ttf");
                text[i].setSize(18);
                text[i].setColor(sf::Color::Black);
                text[i].setPosition(295,130+20*(pos+2));
            }
        }
    }
       
}

Puntuacion::Puntuacion(const Puntuacion& orig) {
    
}

Puntuacion::~Puntuacion() {
    punt->saveToFile();
    delete punt;
    delete[] text;
    delete tablero;
    if(nueva!=NULL)
        delete nueva;
}

void Puntuacion::writeName(std::string txt){
    if(pos!=-1){
        //ESCRIBE SEGUN LA POSICION
        text[7].setString(txt);
        if(pos==0){punt->set("1Name",txt);}
        if(pos==1){punt->set("2Name",txt);}
        if(pos==2){punt->set("3Name",txt);}
        if(pos==3){punt->set("4Name",txt);}
        if(pos==4){punt->set("5Name",txt);}
    }
    
}
    