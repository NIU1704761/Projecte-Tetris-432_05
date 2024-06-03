#ifndef INFO_JOC_H
#define INFO_JOC_H

#include "GraphicManager.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

//Typedef per determinar el tipus de tecla que s'ha près.
typedef enum
{
    TECLA_ESQUERRA,
    TECLA_DRETA,
    TECLA_AMUNT,
    TECLA_ABAIX,
    TECLA_ESPAI,
    TECLA_ESCAPE,
    NO_TECLA
} TipusTecla;

//Typedef per determinar el tipus de moviment.
typedef enum
{
    MOVIMENT_ESQUERRA = 0,
    MOVIMENT_DRETA,
    MOVIMENT_GIR_HORARI,
    MOVIMENT_GIR_ANTIHORARI,
    MOVIMENT_BAIXA,
    MOVIMENT_BAIXA_FINAL
}TipusMoviment;

//Número de figures possibles.
const int N_TIPUS_FIGURES = 7;

//Typedef que determina els color de les figures.
typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR,
    COLOR_GRIS //Afegim el color gris.
} ColorFigura;

//Typedef que determina els tipus de figures.
typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S
} TipusFigura;

//Valors màxims de l'amplada i l'alçada de la matriu on es representa les figures.
const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

//Typedef per determinar el sentit del gir.
typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

// Tamany de la pantalla gràfica
const int SCREEN_SIZE_X = 700;
const int SCREEN_SIZE_Y = 700;

// Mida dels quadrats que formen el tauler
const int MIDA_QUADRAT = 26;

// Tamany del tauler
const int N_FILES_TAULER = 21;
const int N_COL_TAULER = 12;

// Posició del tauler a la pantalla
const int POS_X_TAULER = 120;
const int POS_Y_TAULER = 100;

#endif