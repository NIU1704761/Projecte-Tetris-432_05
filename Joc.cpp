#include "Joc.h"

void Joc::inicialitza(const string& nomFitxer) //Inicialitzem la situació de joc segons una informació d'un fitxer.
{
	ifstream fitxer;
	fitxer.open(nomFitxer); //Obrim el fitxer.

	if (fitxer.is_open())
	{
		int tipus, fila, columna, nGirs;

		fitxer >> tipus >> fila >> columna >> nGirs; //Llegim el fitxer i assignem la informació de la figura.

		m_figura.setX(columna - 1); //Assignem la coordenada 'x' de referència de la figura.
		m_figura.setY(fila - 1); //Assignem la coordenada 'y' de referència de la figura.
		m_figura.inicilitza((TipusFigura)tipus, columna - 1, fila - 1); //Inicialitzem la figura per saber quina forma té.

		for (int i = 0; i < nGirs; i++) //Girar en sentit horari la figura tants cops com indici el document a nGirs.
		{
			m_figura.girar(GIR_HORARI);
		}

		int casella;
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer >> casella;
				m_tauler.setCasella((ColorFigura)casella, i, j); //Assignem cada posició del tauler amb la informació del fitxer.
			}
		}

	}

	fitxer.close(); //Tanquem el fitxer.
}

void Joc::escriuTauler(const string& nomFitxer) //Funció per reescriure el fitxer amb els canvis pertinents.
{
	ofstream fitxer;
	fitxer.open(nomFitxer); //Obrim el fitxer.

	if (fitxer.is_open())
	{
		ColorFigura actualTauler[MAX_FILA][MAX_COL]; //Matriu per representar el tauler actual.
		m_tauler.getMatriu(actualTauler, m_figura); //Assignem a la matriu anterior la informació del tauler i de la figura.

		for (int i = 0; i < MAX_FILA; i++) //Enviem al fitxer la informació de cada una de les posicions del tauler separades entre elles per un espai.
		{
			for (int j = 0; j < MAX_COL; j++)
				fitxer << actualTauler[i][j] << " ";
			fitxer << endl;
		}
		fitxer.close(); //Tanquem el fitxer.
	}

}

int Joc::baixaFigura() //Funció per baixar la figura.
{
	int nElim = 0;
	bool noBaixa;

	Figura temp = m_figura; //Creem una figura temporal per comprobar si pot baixar.
	temp.baixar(); //La baixem.
	noBaixa = m_tauler.colisiona(temp); //Comprovem si colisiona.

	if (!noBaixa)
	{
		m_figura.baixar(); //Si no colisiona, baixem la figura. 

	}
	else
	{
		ColorFigura copiaFigura[MAX_ALCADA][MAX_AMPLADA];
		m_figura.getMatriu(copiaFigura);
		int x, y, amplada, alcada;

		x = m_figura.getX();
		y = m_figura.getY();
		amplada = m_figura.getAmplada();
		alcada = m_figura.getAlcada();

		for (int i = 0; i < alcada; i++)
		{
			for (int j = 0; j < amplada; j++)
			{
				if (copiaFigura[i][j] != COLOR_NEGRE)
				{
					m_tauler.setCasella(copiaFigura[i][j], y + i, x + j); //Si colisiona, la col·loquem dins del tauler a la posició en la que s'ha quedat.
				}
			}
		}

		nElim = m_tauler.eliminarFiles(); //Comprovem les files eliminades. 
		m_figura.inicilitza(NO_FIGURA, 0, 0); //Modifiquem els valors de la figura per tal que estigui buida, ja que ja s'ha col·locat i forma part del tauler.
	}

	return nElim;
}

bool Joc::mouFigura(int dirX) //Funció per moure una figura.
{
	Figura temp = m_figura; //Figura temporal per comprovar si es poden realitzar els moviments.
	bool moviment = false;
	temp.movimentHoritzontal(dirX); //Comprovem els moviments de la figura temporal.
	
	if (!m_tauler.colisiona(temp)) //Si la temporal no colisiona, es realitza el moviment amb la figura i moviment possible.
	{
		m_figura.movimentHoritzontal(dirX);
		moviment = true;
	}

	return moviment; //Retornem si el moviment és possible o no.
		
}

bool Joc::giraFigura(DireccioGir direccio) //Funció per girar una figura.
{
	bool noGira;
	Figura temp = m_figura; //Figura temporal per comprovar si el moviment és possible.
	
	temp.girar(direccio); //Girem la temporal.
	noGira = m_tauler.colisiona(temp); //Comprovem si col·lisiona.

	if (!noGira)
	{
		m_figura.girar(direccio); //Si no col·lisiona girem la figura.
	}

	return noGira; //Retornem si el gir és possible o no.
}