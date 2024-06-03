#ifndef FIGURA_H
#define FIGURA_H

#include "InfoJoc.h"

class Figura
{
public:
    Figura(); //Constructor de Figura per inicialitzar-la a 0.

    void setX(int x) { m_x = x; } //Setter de la variable m_x.
    void setY(int y) { m_y = y; } //Setter de la variable m_y.
    void setColor(const ColorFigura& color) { m_color = color; } //Setter del color d'una figura.

    int getX() const { return m_x; } //Getter de la variable m_x. 
    int getY() const { return m_y; } //Getter de la variable m_y.
    int getAmplada() const { return m_amplada; } //Getter de la variable m_amplada.
    int getAlcada() const { return m_alcada; } //Getter de la variable m_alcada.
    void getMatriu(ColorFigura matriu[MAX_ALCADA][MAX_AMPLADA]) const; //Getter de la matriu m_figura.
    ColorFigura getPosicio(int i, int j) const { return m_figura[i][j]; } //Getter del color d'una posici� de m_figura.

    void inicialitza(TipusFigura figura, int x, int y); //Funci� per inicilitzar la matriu de la figura.
    void figuraAleatoria(); //Funci� per generar una figura aleatoria.

    void movimentHoritzontal(int dirX) { m_x += dirX; } //Funci� per determinar el moviment horitzontal de la figura.
    void baixar() { m_y++; } //Funci� per determinar la baixada de la figura.
    void girar(DireccioGir gir); //Funci� per determinar el gir de la figura.
    
    void dibuixaFigura() const; //Funci� per dibuixar la figura.    
    void dibuixaSeguent() const; //Funci� per dibuixar la seg�ent figura.
    void dibuixaSeguent2() const; //Funci� per dibuixar la 2na figura seg�ent.
    void dibuixaSeguent3() const; //Funci� per dibuixar la 3ra figura seg�ent.
    void dibuixaFantasma() const; //Funci� per dibuixar la figura fantasma.

private:
    ColorFigura m_figura[MAX_AMPLADA][MAX_ALCADA]; //Variable de tipus ColorFigura on es guarda la figura en forma de matriu.
    ColorFigura m_color; //Variable per guardar el color de la figura.
    TipusFigura m_tipus; //Variable per guardar el tipus de figura.
    int m_x; //Variable per guardar la coordenada 'x' de la posici� de refer�ncia de la matriu.
    int m_y; //Variable per guardar la coordenada 'y' de la posici� de refer�ncia de la matriu.
    int m_amplada; //Variable per guardar l'amplada real de la figura.
    int m_alcada; //Variable per guardar l'al�ada real de la figura.
    
    void transposarMatriu(); //Funci� per transposar matrius.
    void girHorari(); //Funci� que defineix el gir horari d'una figura.
    void girAntihorari(); //Funci� que defineix el gir anti-horari d'una figura.
    int Aleatori(int NumMax); //Funci� per generar un n�mero aleatori.
};


#endif
