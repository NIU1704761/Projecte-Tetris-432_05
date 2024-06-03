#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

class Tauler
{
public:
	Tauler(); //Constructor que inicialitza el tauler de color negre (tot 0).

	void setCasella(ColorFigura casella, int i, int j) { m_tauler[i][j] = casella; } //Setter d'una posició concreta del tauler.

	ColorFigura getCasella(int i, int j) const { return m_tauler[i][j]; } //Getter d'una posició concreta del tauler.
	void getMatriu(ColorFigura matriu[N_FILES_TAULER][N_COL_TAULER], Figura& figura) const; //Getter del tauler amb una figura a dins.

	bool colisiona(Figura& figura) const; //Funció per determinar si una figura col·lisiona amb elements del tauler.
	int eliminarFiles(); //Funció per eliminar files.
	bool taulerPle(Figura& figura) const; //Funció per comprovar si no es pot generar una nova figura.

	void dibuixaTauler(); //Funció per dibuixar el tauler amb les peces col·locades.

private:
	ColorFigura m_tauler[N_FILES_TAULER][N_COL_TAULER]; //Matriu de ColorFigura que representa el tauler (possibilitat de fer-lo més gran en un futur, ja sigui per gameplay o estètica).

};
#endif