#ifndef MOVIMENT_H
#define MOVIMENT_H

#include <iostream>
#include <fstream>
#include "InfoJoc.h"

using namespace std;

class Moviment //Classe node dels moviments.
{
public:
	Moviment(const TipusMoviment& moviment) : m_moviment(moviment), m_seguent(nullptr) {} //Constructor de la classe.

	TipusMoviment getMoviment() const { return m_moviment; } //Getter del moviment del node.
	Moviment* getSeguent() const { return m_seguent; } //Getter del node següent.

	void setSeguent(Moviment* seguent) { m_seguent = seguent; } //Setter del node següent.

private:
	TipusMoviment m_moviment; //Moviment del node.
	
	Moviment* m_seguent; //Node següent.

};

#endif