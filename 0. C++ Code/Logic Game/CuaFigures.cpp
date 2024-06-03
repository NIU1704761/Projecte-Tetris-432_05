#include "CuaFigures.h"

CuaFigures::~CuaFigures() //Destructor.
{
	while (!esBuida()) //Sempre que no estigui buida.
		treu(); //Treu el primer element.
}

void CuaFigures::afegeix(const Figures& figura) //Funci� per afegir un element
{
	Figures* novaFigura = new Figures(figura); //Declarem un nou node figura.
	if (esBuida()) //Si la cua est� buida.
	{
		m_cap = novaFigura; //El primer element ser� el nou node.
		m_ultim = novaFigura; //L'�ltim element ser� el nou node.
	}
	else //Si la cua no est� buida.
	{
		m_ultim->setSeguent(novaFigura); //Accedim al node al que est� apuntant l'�ltim i l'assignem a la nova figura.
		m_ultim = novaFigura; //Modifiquem per tal que la nova figura sigui l'�ltima.
	}
}

void CuaFigures::treu() //Funci� que treu el primer element de la cua.
{
	if (!esBuida()) //Si la cua no est� buida.
	{
		Figures* figuraEliminar = m_cap; //Determinem el node a eliminar.
		m_cap = m_cap->getSeguent(); //Fem que el nou primer element sigui el node al que apuntava el primer abans.
		delete figuraEliminar; //Eliminem l'antic primer element.

		if (m_cap == nullptr) //Si el primer element �s null (nom�s quedava un element a la llista).
			m_ultim = nullptr; //L'�ltim element tamb� �s null.
	}
	else //Si la cua est� buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

Figures& CuaFigures::getPrimer() const //Getter del primer element de la cua.
{
	if (!esBuida()) //Si la cua no est� buida.
		return *m_cap; //Retornem el primer node de la cua.
	else //Si la cua est� buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

Figures& CuaFigures::getUltim() const //Getter de l'�ltim element de la cua.
{
	if (!esBuida()) //Si la cua no est� buida.
		return *m_ultim; //Retornem l'�ltim node de la cua.
	else //Si la cua est� buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

bool CuaFigures::esBuida() const //Funci� per determinar si la cua est� buida.
{
	return m_cap == nullptr; //Retornem 1 si el primer element de la cua �s nullptr i 0 si no ho �s.
}