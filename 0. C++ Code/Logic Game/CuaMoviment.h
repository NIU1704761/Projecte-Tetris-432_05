#ifndef CUAMOVIMENT_H
#define CUAMOVIMENT_H


#include "Moviments.h"

class CuaMoviment
{
public:
	CuaMoviment() : m_cap(nullptr), m_ultim(nullptr) {} //Constructor de la classe.
	~CuaMoviment(); //Destructor de la classe.

	Moviment& getPrimer() const;  //Getter del primer element de la cua.
	Moviment& getUltim() const; //Getter de l'últim element de la cua.

	void afegeix(const Moviment& moviment); //Funció per afegir un node al final de la cua.
	void treu(); //Funció per treure el primer node de la cua.
	
	bool esBuida() const; //Funció per comprovar si la cua està buida.

private:
	Moviment* m_cap; //Primer node de la cua.
	Moviment* m_ultim; //Últim node de la cua.

};

#endif 