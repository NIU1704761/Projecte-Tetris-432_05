#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "Joc.h"
#include "CuaMoviment.h"

using namespace std;

class Partida
{
public:
    Partida(); //Constructor de la classe.

    int getPunts() const { return m_puntuacio; } //Getter dels punts de la partida.
    int getNivell() const { return m_nivell; } //Getter del nivell de la partida.

    void setNivell(int nivell) { m_nivell = nivell; } //Setter del nivell de la partida.

    void inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments); //Funció que inicialitza una partida, ja sigui per fitxer o no.
    void actualitza(int mode, double deltaTime); //Funció que actualitza en funció del mode.
    
    void pausa(); //Funció que mostra la pantalla de pausa.
    bool acabarPartida(); //Funció que mostra la pantalla d'acabar partida.

private:
    double m_temps; //Temps de la partida.
    int m_puntuacio; //Punts de la partida.
    int m_nivell; //Nivell de la partida.
    double m_velocitat; //Velocitat de la partida.
    Joc m_joc; //Joc.
    
    CuaMoviment m_moviments; //Llista de moviments.

    void actualitzaJoc(double deltaTime); //Funció que actualitza el mode joc.
    void actualitzaFitxer(double deltaTime); //Funció que actualitza el mode test
    void puntuacio(int nElim); //Funció que defineix les puntuacions i el nivell del joc.
    void inicialitzaMoviments(const string& fitxerMoviments); //Funció que inicialitza la llista de moviments per fitxer.

};

#endif 
