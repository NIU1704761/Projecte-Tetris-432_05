#include "CuaMoviment.h"

CuaMoviment::~CuaMoviment() //Destructor.
{
	while (!esBuida()) //Sempre que no estigui buida.
		treu(); //Treu el primer element.
}

void CuaMoviment::afegeix(const Moviment& moviment) //Funció per afegir un element
{
	Moviment* nouMoviment = new Moviment(moviment); //Declarem un nou node moviment.
	if (esBuida()) //Si la cua està buida.
	{
		m_cap = nouMoviment; //El primer element serà el nou node.
		m_ultim = nouMoviment; //L'últim element serà el nou node.
	}
	else //Si la cua no està buida.
	{
		m_ultim->setSeguent(nouMoviment); //Accedim al node al que està apuntant l'últim i l'assignem al nou moviment.
		m_ultim = nouMoviment; //Modifiquem per tal que el nou moviment sigui l'últim.
	}
}

void CuaMoviment::treu() //Funció que treu el primer element de la cua.
{
	if (!esBuida()) //Si la cua no està buida.
	{
		Moviment* movimentEliminar = m_cap; //Determinem el node a eliminar.
		m_cap = m_cap->getSeguent(); //Fem que el nou primer element sigui el node al que apuntava el primer abans.
		delete movimentEliminar; //Eliminem l'antic primer element.

		if (m_cap == nullptr) //Si el primer element és null (només quedava un element a la llista).
			m_ultim = nullptr; //L'últim element també és null.
	}
	else //Si la cua està buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

Moviment& CuaMoviment::getPrimer() const //Getter del primer element de la cua.
{
	if (!esBuida()) //Si la cua no està buida.
		return *m_cap; //Retornem el primer node de la cua.
	else //Si la cua està buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

Moviment& CuaMoviment::getUltim() const //Getter de l'últim element de la cua.
{
	if (!esBuida()) //Si la cua no està buida.
		return *m_ultim; //Retornem l'últim node de la cua.
	else //Si la cua està buida, missatge d'error.
		cout << "Error: Empty list." << endl;
}

bool CuaMoviment::esBuida() const //Funció per determinar si la cua està buida.
{
	return m_cap == nullptr; //Retornem 1 si el primer element de la cua és nullptr i 0 si no ho és.
}