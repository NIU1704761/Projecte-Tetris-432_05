#ifndef CUAFIGURES_H
#define CUAFIGURES_H

#include "Figures.h"

class CuaFigures
{
public:
	CuaFigures() : m_cap(nullptr), m_ultim(nullptr) {} //Constructor de la classe.
	~CuaFigures(); //Destructor de la classe.

	Figures& getPrimer() const; //Getter del primer element de la cua.
	Figures& getUltim() const; //Getter de l'�ltim element de la cua.

	void afegeix(const Figures& figura); //Funci� per afegir un node al final de la cua.
	void treu(); //Funci� per treure el primer node de la cua.

	bool esBuida() const; //Funci� per comprovar si la cua est� buida.
private:
	Figures* m_cap; //Primer node de la cua.
	Figures* m_ultim; //�ltim node de la cua.
};

#endif
