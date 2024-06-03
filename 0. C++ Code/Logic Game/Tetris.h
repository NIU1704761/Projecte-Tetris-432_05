#ifndef TETRIS_H
#define TETRIS_H

#include "Partida.h"
#include "LlistaJugadors.h"
#include <iostream>

using namespace std;

class Tetris
{
public:
	Tetris() { m_pause = false; } //Constructor de classe.

	int juga(int mode, Screen& pantalla); //Funció per mostrar i jugar una partida.

	void mostraPuntuacions(); //Funció per mostrar les puntuacions per pantalla.
	void afegeixPuntuacio(int puntuacio, const string& nom); //Funció per afegir a la llista de puntuacions un node nou.

	void opcions(); //Funció que mostra el primer menú.
	void menu(); //Funció per mostrar el menú.
	void controls(); //Funció per veure els controls.
	void puntuacions(); //Funció per veure com es sumen les puntuacions.
	int confirmar(int mode); //Funció per confirmar tornar al menú.
	int confirmar2(int mode); //Funció per confirmar la sortida de la terminal.

private:
	Partida m_partida; //Partida de joc.
	bool m_pause; //Pausa del joc.

	LlistaJugadors m_llista; //Llista de jugadors.

	void mostrarPantalla(int mode, Screen& pantalla); //Funció per mostrar una partida.
	int jugaNormal(Screen& pantalla); //Funció per mostrar i jugar una partida normal.
	void jugaTest(Screen& pantalla); //Funció per mostrar i jugar una partida test.
};
#endif