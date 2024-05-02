#include "Tauler.h"

Tauler::Tauler() //Constructor de Tauler que l'inicialitza tot a color negre.
{
	for (int i = 0; i < MAX_FILA; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			m_tauler[i][j] = COLOR_NEGRE; //Cada posició del tauler s'inicialitza en negre.
		}
	}
}

void Tauler::getMatriu(ColorFigura matriu[MAX_FILA][MAX_COL], Figura& figura) //Funció per aconseguir el tauler amb una figura col·locada.
{
	for (int i = 0; i < MAX_FILA; i++)
		for (int j = 0; j < MAX_COL; j++)
			matriu[i][j] = m_tauler[i][j]; //Treballem sobre una matriu que representi el tauler.

	int x = figura.getX(); //Coordenada 'x' de referència.
	int y = figura.getY(); //Coordenada 'y' de referència.
	int alcada = figura.getAlcada(); //Obtenim l'alçada real de la figura.
	int amplada = figura.getAmplada(); //Obtenim l'amplada real de la figura.
	ColorFigura matriuFigura[MAX_ALCADA][MAX_AMPLADA]; //Matriu que representa la figura.
	figura.getMatriu(matriuFigura); //Omplim la matriu amb la informació de la figura.

	for (int i = 0; i < alcada; i++)
		for (int j = 0; j < amplada; j++)
			if (matriuFigura[i][j] != COLOR_NEGRE)
				matriu[i + y][j + x] = matriuFigura[i][j]; //Cada posició no negre de la figura s'assigna a la posició pertinent segons les coordenades de la figura dins del tauler (i + y, j + x).
}

bool Tauler::colisiona(Figura& figura) const //Funció per comprobar les col·lisions.
{
	bool colisiona = false; //Valor que retornarem per saber si col·lisiona.

	ColorFigura copiaFigura[MAX_ALCADA][MAX_AMPLADA]; //Creem una copia de la figura que "simular" els moviments i realitzar-los si són possibles.
	figura.getMatriu(copiaFigura); //Omplim la matriu amb la informació de la figura.
	int x = figura.getX(); //Coordenada 'x' de referència.
	int y = figura.getY(); //Coordenada 'y' de referència.
	int amplada = figura.getAmplada(); //Obtenim l'amplada real de la figura.
	int alcada = figura.getAlcada(); //Obtenim l'alçada real de la figura.

	if (x < 0) //Si la coordenada 'x' se surt del taulell per l'esquerra (overflow del tauler)
	{
		int i = 0;
		int j = (-1) * (x + 1); //Columna en la que es troben les coordenades de referència de la figura.
		
		while ((!colisiona) && (i < alcada)) //Mentres no hi hagi colisions i la coordenada 'y'(i) sigui més petita que l'alçada de la figura.
		{
			if (copiaFigura[i][j] != COLOR_NEGRE) //Si una posició de la figura que es troba fora del tauler no és de color negre, colisiona.
			{
				colisiona = true;
			}
			else //Si no colisiona, revisar la següent columna.
			{
				i++;
			}
		}
	}

	if (((x + amplada) > MAX_COL) && (!colisiona)) //Si la coordenada 'x' se surt del taulell per la dreta (overflow del tauler)
	{
		int i = 0; 
		int j = MAX_COL - x; //Columna en la que es troben les coordenades de referència de la figura.

		while ((!colisiona) && (i < alcada)) //Mentres no hi hagi colisions i la coordenada 'y'(i) sigui més petita que l'alçada de la figura.
		{
			if (copiaFigura[i][j] != COLOR_NEGRE) //Si una posició de la figura que es troba fora del tauler no és de color negre, colisiona.
			{
				colisiona = true;
			}
			else //Si no colisiona, revisar la següent columna.
			{
				i++;
			}
		}
	}

	if (((y + alcada) > MAX_FILA) && (!colisiona)) //Si la coordenada 'y' se surt del taulell per sota (overflow del taulell)
	{
		int j = 0;
		int i = MAX_FILA - y; //Fila en la que es troben les coordenades de referència de la figura.

		while ((!colisiona) && (j < amplada)) //Mentres no hi hagi colisions i la coordenada 'x'(j) sigui més petita que l'amplada de la figura.
		{
			if (copiaFigura[i][j] != COLOR_NEGRE) //Si una posició de la figura que es troba fora del tauler no és de color negre, colisiona.
			{
				colisiona = true;
			}
			else //Si no colisiona, revisar la següent fila.
			{
				j++;
			}
		}
	}


	if (!colisiona) //Si a partir d'aquest punt no hi ha situacions d'overflow, comprobem si colisiona amb altres figures.
	{
		int i = 0;
		int j;

		while ((i < alcada) && (!colisiona)) //Mentres no hi hagi colisions i la coordenada 'y'(i) sigui més petita que l'alçada de la figura.
		{
			j = 0;

			while ((j < amplada) && (!colisiona)) //Mentres no hi hagi colisions i la coordenada 'x'(j) sigui més petita que l'amplada de la figura.
			{
				if ((copiaFigura[i][j] != COLOR_NEGRE) && (m_tauler[i + y][j + x] != COLOR_NEGRE)) //Si una posició de la figura i la posició del tauler que ocupa aquesta mateixa posició de la figura no són de color negre, hi ha colisió.
				{
					colisiona = true;
				}
				else //Si no colisiona, revisar la següent fila.
				{
					j++;
				}
			}
			i++; //Revisar la següent columna.
		}
	}

	return colisiona; //Retornem el bool.
}

int Tauler::eliminarFiles() //Funció per eliminar files plenes.
{
	int nEliminades = 0; //Contador de les files eliminades que retornarem.

	for (int i = 0; i < MAX_FILA; i++) //Per cada fila del tauler.
	{
		bool filaPlena = true;
		int j = 0;

		while ((j < MAX_COL) && (filaPlena)) //Si estem dins dels valors de les columnes del tauler i la fila està plena.
		{
			if (m_tauler[i][j] == COLOR_NEGRE) //Si hi ha alguna posició del tauler que estigui buida, la fila en la que es trobi no està plena.
			{
				filaPlena = false;
			}
			else //Si no, passar a la següent columna.
			{
				j++;
			}
		}

		if (filaPlena) //Si la fila està plena, es baixa la que hi ha a sobre i es buida la de dalt.
		{
			for (int y = i; y > 0; y--) //A partir de la fila plena i pujant fins la fila 0.
			{
				for (int x = 0; x < MAX_COL; x++) //Per cada posició dins d'aquesta fila.
				{
					m_tauler[y][x] = m_tauler[y - 1][x]; //Baixem els valor de la fila de sobre..
				}
			}

			for (int x = 0; x < MAX_COL; x++) //Per cada posició de la primera fila.
			{
				m_tauler[0][x] = COLOR_NEGRE; //Indiquem que la primera fila queda buida.
			}

			nEliminades++; //S'incrementa el número de files eliminades.
		}
	}

	return nEliminades; //Retornem el número de files eliminades.
}