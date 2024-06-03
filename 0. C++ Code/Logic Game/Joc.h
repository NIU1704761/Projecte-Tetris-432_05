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

	int getY() const { return m_figura.getY(); } //Getter de la posici� y de la figura.

	void inicialitza(); //Funci� per inicialitzar la situaci� de joc.
	bool acabarJoc(); //Funci� per acabar el joc.
	void inicialitzaFitxer(const string& nomFitxer); //Funci� que inicialitza la situaci� de joc per fitxer.
	void inicialitzaFigures(const string& fitxerFigures); //Funci� per inicialitzar una cua de figures per fitxer.
	
	int baixaFigura(int mode); //Funci� que baixa les figures.
	int baixaFigura2(int mode); //Funci� que baixa les figures de cop.
	bool mouFigura(int dirX); //Funci� que mou les figures.
	bool giraFigura(const DireccioGir& direccio); //Funci� que gira les figures.
	
	void baixaFantasma(); //Funci� que baixa la figura fantasma.

	void dibuixaJoc(); //Funci� que dibuixa la situaci� de joc.
	
private:
	Tauler m_tauler; //Variable que representa el tauler del joc.
	
	Figura m_figura; //Variable que representa la figura amb la que es juga.
	Figura m_fantasma; //Ombra de la figura amb la que es juga.
	
	Figura m_figuraSeguent; //Figura seg�ent.
	Figura m_figuraSeguent2; //Figura seg�ent.
	Figura m_figuraSeguent3; //Figura seg�ent.
	
	CuaFigures m_figures; //Llista (cua) de figures.

	void buidarPantalla(); //Funci� per buidar la pantalla.
	void acabarMoviment(int mode); //Funci� per acabar el moviment de baixar, depenent del mode.
};

#endif