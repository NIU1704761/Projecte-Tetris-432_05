#ifndef JOC_H
#define JOC_H

#include "Tauler.h"
#include "Figura.h"
#include <string>
#include <fstream>
#include "CuaFigures.h"

using namespace std;

class Joc
{
public:
	Joc() {}; //Constructor de Joc.

	int getY() const { return m_figura.getY(); } //Getter de la posició y de la figura.

	void inicialitza(); //Funció per inicialitzar la situació de joc.
	bool acabarJoc(); //Funció per acabar el joc.
	void inicialitzaFitxer(const string& nomFitxer); //Funció que inicialitza la situació de joc per fitxer.
	void inicialitzaFigures(const string& fitxerFigures); //Funció per inicialitzar una cua de figures per fitxer.
	
	int baixaFigura(int mode); //Funció que baixa les figures.
	int baixaFigura2(int mode); //Funció que baixa les figures de cop.
	bool mouFigura(int dirX); //Funció que mou les figures.
	bool giraFigura(const DireccioGir& direccio); //Funció que gira les figures.
	
	void baixaFantasma(); //Funció que baixa la figura fantasma.

	void dibuixaJoc(); //Funció que dibuixa la situació de joc.
	
private:
	Tauler m_tauler; //Variable que representa el tauler del joc.
	
	Figura m_figura; //Variable que representa la figura amb la que es juga.
	Figura m_fantasma; //Ombra de la figura amb la que es juga.
	
	Figura m_figuraSeguent; //Figura següent.
	Figura m_figuraSeguent2; //Figura següent.
	Figura m_figuraSeguent3; //Figura següent.
	
	CuaFigures m_figures; //Llista (cua) de figures.

	void buidarPantalla(); //Funció per buidar la pantalla.
	void acabarMoviment(int mode); //Funció per acabar el moviment de baixar, depenent del mode.
};

#endif