#include "Tauler.h"

Tauler::Tauler() //Constructor de Tauler que l'inicialitza tot a color negre.
{
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			m_tauler[i][j] = COLOR_NEGRE;
		}
	}
}

void Tauler::getMatriu(ColorFigura matriu[MAX_FILA][MAX_COL], Figura& figura) //Funció per aconseguir el tauler amb una figura col·locada.
{
	for (int i = 0; i < MAX_FILA; i++)
		for (int j = 0; j < MAX_COL; j++)
			matriu[i][j] = m_tauler[i][j]; //Treballem sobre una matriu que representi el tauler.

	int x = figura.getX();
	int y = figura.getY();
	int alcada = figura.getAlcada();
	int amplada = figura.getAmplada();
	ColorFigura matriuFigura[MAX_ALCADA][MAX_AMPLADA]; //Matriu que representa la figura.
	figura.getMatriu(matriuFigura); //Omplim la matriu amb la informació de la figura.

	for (int i = 0; i < alcada; i++)
		for (int j = 0; j < amplada; j++)
			if (matriuFigura[i][j] != COLOR_NEGRE)
				matriu[i + y][j + x] = matriuFigura[i][j]; //Cada posició no negre de la figura s'assigna a la posició pertinent segons les coordenades de la figura dins del tauler.
}

bool Tauler::colisiona(Figura& figura) const //Funció per comprobar les col·lisions.
{
	bool colisiona = false; //Valor que retornarem per saber si col·lisiona.

	ColorFigura copiaFigura[MAX_ALCADA][MAX_AMPLADA]; //Creem una copia de la figura que "simular" els moviments i realitzar-los si són possibles.
	figura.getMatriu(copiaFigura);
	int x = figura.getX();
	int y = figura.getY();
	int amplada = figura.getAmplada();
	int alcada = figura.getAlcada();

	if (x < 0) //Si la coordenada 'x' se surt del taulell per l'esquerra (overflow del tauler)
	{
		int i = 0;
		int j = (-1) * (x + 1); //Columna en la que es troben les coordenades de referència de la figura.
		
		while ((!colisiona) && (i < alcada))
		{
			if (copiaFigura[i][j] != COLOR_NEGRE) //Si una posició de la figura que es troba fora del tauler no és de color negre, colisiona.
			{
				colisiona = true;
			}
			else
			{
				i++;
			}
		}
	}

	if (((x + amplada) > MAX_COL) && (!colisiona)) //Si la coordenada 'x' se surt del taulell per la dreta (overflow del tauler)
	{
		int i = 0; 
		int j = MAX_COL - x; //Columna en la que es troben les coordenades de referència de la figura.

		while ((!colisiona) && (i < alcada))
		{
			if (copiaFigura[i][j] != COLOR_NEGRE) //Si una posició de la figura que es troba fora del tauler no és de color negre, colisiona.
			{
				colisiona = true;
			}
			else
			{
				i++;
			}
		}
	}

	if (((y + alcada) > MAX_FILA) && (!colisiona)) //Si la coordenada 'y' se surt del taulell per sota (overflow del taulell)
	{
		int j = 0;
		int i = MAX_FILA - y; //Fila en la que es troben les coordenades de referència de la figura.

		while ((!colisiona) && (j < amplada))
		{
			if (copiaFigura[i][j] != COLOR_NEGRE) //Si una posició de la figura que es troba fora del tauler no és de color negre, colisiona.
			{
				colisiona = true;
			}
			else
			{
				j++;
			}
		}
	}


	if (!colisiona) //Si a partir d'aquest punt no hi ha situacions d'overflow, comprobem si colisiona amb altres figures.
	{
		int i = 0;
		int j;

		while ((i < amplada) && (!colisiona))
		{
			j = 0;

			while ((j < alcada) && (!colisiona))
			{
				if ((copiaFigura[i][j] != COLOR_NEGRE) && (m_tauler[i + y][j + x] != COLOR_NEGRE)) //Si una posició de la figura i la posició del tauler que ocupa aquesta mateixa posició de la figura no són de color negre, hi ha colisió.
				{
					colisiona = true;
				}
				else
				{
					j++;
				}
			}
			i++;
		}
	}

	return colisiona; //Retornem el bool.
}

int Tauler::eliminarFiles() //Funció per eliminar files plenes.
{
	int nEliminades = 0; //Contador de les files eliminades que retornarem.

	for (int i = 0; i < MAX_FILA; i++)
	{
		bool filaPlena = true;
		int j = 0;

		while ((j < MAX_COL) && (filaPlena))
		{
			if (m_tauler[i][j] == COLOR_NEGRE) //Si ja alguna posició del tauler que estigui buida, la fila en la que es trobi no està plena.
			{
				filaPlena = false;
			}
			else
			{
				j++;
			}
		}

		if (filaPlena) //Si la fila està plena, es baixa la que hi ha a sobre i es buida la de dalt.
		{
			for (int y = i; y > 0; y--)
			{
				for (int x = 0; x < MAX_COL; x++)
				{
					m_tauler[y][x] = m_tauler[y - 1][x]; //Baixem els valor d'una fila.
				}
			}

			for (int y = 0; y < MAX_COL; y++)
			{
				m_tauler[0][y] = COLOR_NEGRE; //Indiquem que la primera fila queda buida.
			}

			nEliminades++; //S'incrementa el número de files eliminades.
		}
	}

	return nEliminades;
}