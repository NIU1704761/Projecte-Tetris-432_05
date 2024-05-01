#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
	Tauler(); //Constructor que inicialitza el tauler de color negre (tot 0).
	void setCasella(ColorFigura casella, int x, int y) { m_tauler[x][y] = casella; } //Setter d'una posició concreta del tauler.
	ColorFigura getCasella(int x, int y) const { return m_tauler[x][y]; } //Getter d'una posició concreta del tauler.
	void getMatriu(ColorFigura matriu[MAX_FILA][MAX_COL], Figura& figura); //Getter del tauler amb una figura a dins.
	bool colisiona(Figura& figura) const; //Funció per determinar si una figura col·lisiona amb elements del tauler.
	int eliminarFiles(); //Funció per eliminar files.
private:
	ColorFigura m_tauler[MAX_FILA][MAX_COL]; //Matriu de ColorFigura que representa el tauler (possibilitat de fer-lo més gran en un futur, ja sigui per gameplay o estètica).
};
#endif