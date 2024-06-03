#include "CuaFigures.h"

CuaFigures::~CuaFigures() //Destructor.
{
	while (!esBuida()) //Sempre que no estigui buida.
		treu(); //Treu el primer element.
}

void CuaFigures::afegeix(const Figures& figura) //Funció per afegir un element
{
	Figures* novaFigura = new Figures(figura); //Declarem un nou node figura.
	if (esBuida()) //Si la cua està buida.
	{
		m_cap = novaFigura; //El primer element serà el nou node.
		m_ultim = novaFigura; //L'últim element serà el nou node.
	}
	else //Si la cua no està buida.
	{
		m_ultim->setSeguent(novaFigura); //Accedim al node al que està apuntant l'últim i l'assignem a la nova figura.
		m_ultim = novaFigura; //Modifiquem per tal que la nova figura sigui l'última.
	}
}

void CuaFigures::treu() //Funció que treu el primer element de la cua.
{
	if (!esBuida()) //Si la cua no està buida.
	{
		Figures* figuraEliminar = m_cap; //Determinem el node a eliminar.
		m_cap = m_cap->getSeguent(); //Fem que el nou primer element sigui el node al que apuntava el primer abans.
		delete figuraEliminar; //Eliminem l'antic primer element.

		if (m_cap == nullptr) //Si el primer element és null (només quedava un element a la llista).
			m_ultim = nullptr; //L'últim element també és null.
	}
	else //Si la cua està buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

Figures& CuaFigures::getPrimer() const //Getter del primer element de la cua.
{
	if (!esBuida()) //Si la cua no està buida.
		return *m_cap; //Retornem el primer node de la cua.
	else //Si la cua està buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

Figures& CuaFigures::getUltim() const //Getter de l'últim element de la cua.
{
	if (!esBuida()) //Si la cua no està buida.
		return *m_ultim; //Retornem l'últim node de la cua.
	else //Si la cua està buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

bool CuaFigures::esBuida() const //Funció per determinar si la cua està buida.
{
	return m_cap == nullptr; //Retornem 1 si el primer element de la cua és nullptr i 0 si no ho és.
}