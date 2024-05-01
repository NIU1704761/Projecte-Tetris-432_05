#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
#include <fstream>
using namespace std;

class Joc
{
public:
	Joc() {}; //Constructor de Joc.
	void inicialitza(const string& nomFitxer); //Funció que inicialitza la situació de joc.
	bool giraFigura(DireccioGir direccio); //Funció que gira les figures.
	bool mouFigura(int dirX); //Funció que mou les figures.
	int baixaFigura(); //Funció que baixa les figures.
	void escriuTauler(const string& nomFitxer); //Funció que et permet reescriure un fitxer.

private:
	Tauler m_tauler; //Variable que representa el tauler del joc.
	Figura m_figura; //Variable que representa la figura amb la que és juga.
};

#endif