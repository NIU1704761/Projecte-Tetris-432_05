#include "CuaMoviment.h"

CuaMoviment::~CuaMoviment() //Destructor.
{
	while (!esBuida()) //Sempre que no estigui buida.
		treu(); //Treu el primer element.
}

void CuaMoviment::afegeix(const Moviment& moviment) //Funci� per afegir un element
{
	Moviment* nouMoviment = new Moviment(moviment); //Declarem un nou node moviment.
	if (esBuida()) //Si la cua est� buida.
	{
		m_cap = nouMoviment; //El primer element ser� el nou node.
		m_ultim = nouMoviment; //L'�ltim element ser� el nou node.
	}
	else //Si la cua no est� buida.
	{
		m_ultim->setSeguent(nouMoviment); //Accedim al node al que est� apuntant l'�ltim i l'assignem al nou moviment.
		m_ultim = nouMoviment; //Modifiquem per tal que el nou moviment sigui l'�ltim.
	}
}

void CuaMoviment::treu() //Funci� que treu el primer element de la cua.
{
	if (!esBuida()) //Si la cua no est� buida.
	{
		Moviment* movimentEliminar = m_cap; //Determinem el node a eliminar.
		m_cap = m_cap->getSeguent(); //Fem que el nou primer element sigui el node al que apuntava el primer abans.
		delete movimentEliminar; //Eliminem l'antic primer element.

		if (m_cap == nullptr) //Si el primer element �s null (nom�s quedava un element a la llista).
			m_ultim = nullptr; //L'�ltim element tamb� �s null.
	}
	else //Si la cua est� buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

Moviment& CuaMoviment::getPrimer() const //Getter del primer element de la cua.
{
	if (!esBuida()) //Si la cua no est� buida.
		return *m_cap; //Retornem el primer node de la cua.
	else //Si la cua est� buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

Moviment& CuaMoviment::getUltim() const //Getter de l'�ltim element de la cua.
{
	if (!esBuida()) //Si la cua no est� buida.
		return *m_ultim; //Retornem l'�ltim node de la cua.
	else //Si la cua est� buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

bool CuaMoviment::esBuida() const //Funci� per determinar si la cua est� buida.
{
	return m_cap == nullptr; //Retornem 1 si el primer element de la cua �s nullptr i 0 si no ho �s.
}