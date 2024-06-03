#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <string>
#include <fstream>
#include "InfoJoc.h"

using namespace std;

class Figures //Classe node de les figures.
{
public:
	Figures(const TipusFigura& tipus, int fila, int columna, int gir) : m_tipus(tipus), m_fila(fila), m_columna(columna), m_gir(gir), m_seguent(nullptr) {} //Constructor de la classe.

	TipusFigura getTipus() const { return m_tipus; } //Getter del tipus de figura.
	int getFila() { return m_fila; } //Getter de la fila.
	int getColumna() const { return m_columna; } //Getter de la columna.
	int getGir() const { return m_gir; } //Getter del número de girs.
	Figures* getSeguent() const { return m_seguent; } //Getter del node següent.
	
	void setSeguent(Figures* seguent) { m_seguent = seguent; } //Setter del node següent.

private:
	TipusFigura m_tipus; //Tipus de figura
	int m_fila; //Fila en la que es troba la figura.
	int m_columna; //Columna en la que es troba la figura.
	int m_gir; //Número de vegades que ha de girar la figura.
	
	Figures* m_seguent; //Node al que apunta.

};

#endif