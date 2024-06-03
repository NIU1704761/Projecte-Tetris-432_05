#ifndef CUAMOVIMENT_H
#define CUAMOVIMENT_H


#include "Moviments.h"

class CuaMoviment
{
public:
	CuaMoviment() : m_cap(nullptr), m_ultim(nullptr) {} //Constructor de la classe.
	~CuaMoviment(); //Destructor de la classe.

	Moviment& getPrimer() const;  //Getter del primer element de la cua.
	Moviment& getUltim() const; //Getter de l'�ltim element de la cua.

	void afegeix(const Moviment& moviment); //Funci� per afegir un node al final de la cua.
	void treu(); //Funci� per treure el primer node de la cua.
	
	bool esBuida() const; //Funci� per comprovar si la cua est� buida.

private:
	Moviment* m_cap; //Primer node de la cua.
	Moviment* m_ultim; //�ltim node de la cua.

};

#endif 