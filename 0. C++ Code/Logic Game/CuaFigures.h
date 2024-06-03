#ifndef CUAFIGURES_H
#define CUAFIGURES_H

#include "Figures.h"

class CuaFigures
{
public:
	CuaFigures() : m_cap(nullptr), m_ultim(nullptr) {} //Constructor de la classe.
	~CuaFigures(); //Destructor de la classe.

	Figures& getPrimer() const; //Getter del primer element de la cua.
	Figures& getUltim() const; //Getter de l'últim element de la cua.

	void afegeix(const Figures& figura); //Funció per afegir un node al final de la cua.
	void treu(); //Funció per treure el primer node de la cua.

	bool esBuida() const; //Funció per comprovar si la cua està buida.
private:
	Figures* m_cap; //Primer node de la cua.
	Figures* m_ultim; //Últim node de la cua.
};

#endif
