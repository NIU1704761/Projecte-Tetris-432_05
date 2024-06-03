#include "Tauler.h"

Tauler::Tauler() //Constructor de Tauler que l'inicialitza tot a color negre.
{
	for (int i = 0; i < N_FILES_TAULER; i++)
	{
		for (int j = 0; j < N_COL_TAULER; j++)
		{
			m_tauler[i][j] = COLOR_NEGRE; //Recorrem cada posici� del tauler i les inicialitzem negres.
		}
	}
}

void Tauler::getMatriu(ColorFigura matriu[N_FILES_TAULER][N_COL_TAULER], Figura& figura) const //Funci� per aconseguir el tauler amb una figura col�locada.
{
	for (int i = 0; i < N_FILES_TAULER; i++)
		for (int j = 0; j < N_COL_TAULER; j++)
			matriu[i][j] = m_tauler[i][j]; //Treballem sobre una matriu que representi el tauler.

	int x = figura.getX();
	int y = figura.getY();
	int alcada = figura.getAlcada();
	int amplada = figura.getAmplada();
	ColorFigura matriuFigura[MAX_ALCADA][MAX_AMPLADA]; //Matriu que representa la figura.
	figura.getMatriu(matriuFigura); //Omplim la matriu amb la informaci� de la figura.

	for (int i = 0; i < alcada; i++)
		for (int j = 0; j < amplada; j++)
			if (matriuFigura[i][j] != NO_COLOR)
				matriu[i + y][j + x] = matriuFigura[i][j]; //Cada posici� no color de la figura s'assigna a la posici� pertinent segons les coordenades de la figura dins del tauler.
}

bool Tauler::colisiona(Figura& figura) const //Funci� per comprobar les col�lisions.
{
	bool colisiona = false; //Valor que retornarem per saber si col�lisiona.

	ColorFigura copiaFigura[MAX_ALCADA][MAX_AMPLADA]; //Creem una copia de la figura que "simular" els moviments i realitzar-los si s�n possibles.
	figura.getMatriu(copiaFigura);
	int x = figura.getX();
	int y = figura.getY();
	int amplada = figura.getAmplada();
	int alcada = figura.getAlcada();

	if ((x - 1) < 0) //Si la coordenada 'x' se surt del taulell per l'esquerra (overflow del tauler)
	{
		int i = 0;
		int j = (-1) * x; //Columna en la que es troben les coordenades de refer�ncia de la figura.

		while ((!colisiona) && (i < alcada))
		{
			if (copiaFigura[i][j] != NO_COLOR) //Si una posici� de la figura que es troba fora del tauler no �s de color negre, colisiona.
			{
				colisiona = true;
			}
			else
			{
				i++;
			}
		}
	}

	if (((x + amplada) > N_COL_TAULER) && (!colisiona)) //Si la coordenada 'x' se surt del taulell per la dreta (overflow del tauler)
	{
		int i = 0;
		int j = N_COL_TAULER - x; //Columna en la que es troben les coordenades de refer�ncia de la figura.

		while ((!colisiona) && (i < alcada))
		{
			if (copiaFigura[i][j] != NO_COLOR) //Si una posici� de la figura que es troba fora del tauler no �s de color negre, colisiona.
			{
				colisiona = true;
			}
			else
			{
				i++;
			}
		}
	}

	if (((y + alcada) > N_FILES_TAULER) && (!colisiona)) //Si la coordenada 'y' se surt del taulell per sota (overflow del taulell)
	{
		int j = 0;
		int i = N_FILES_TAULER - y; //Fila en la que es troben les coordenades de refer�ncia de la figura.

		while ((!colisiona) && (j < amplada))
		{
			if (copiaFigura[i][j] != NO_COLOR) //Si una posici� de la figura que es troba fora del tauler no �s de color negre, colisiona.
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
				if ((copiaFigura[i][j] != NO_COLOR) && (m_tauler[i + y][j + x] != COLOR_NEGRE)) //Si una posici� de la figura i la posici� del tauler que ocupa aquesta mateixa posici� de la figura no s�n de color negre, hi ha colisi�.
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

bool Tauler::taulerPle(Figura& figura) const //Funci� per determinar si no es poden generar noves figures.
{
	bool ple = false; //Valor que retornarem per saber si est� ple.

	ColorFigura copiaFigura[MAX_ALCADA][MAX_AMPLADA]; //Creem una copia de la figura que "simular" els moviments i realitzar-los si s�n possibles.
	figura.getMatriu(copiaFigura);
	int x = figura.getX();
	int y = figura.getY();
	int amplada = figura.getAmplada();
	int alcada = figura.getAlcada();

	int i = 0;
	int j;
	
	while ((i < amplada) && (!ple))
	{  
		j = 0;

		while ((j < alcada) && (!ple))
		{
			if ((copiaFigura[i][j] != NO_COLOR) && (m_tauler[i + y][j + x] != COLOR_NEGRE)) //Si una posici� de la figura i la posici� del tauler que ocupa aquesta mateixa posici� de la figura no s�n de color negre, hi ha colisi�.
			{
				ple = true;
			}
			else
			{
				j++;
			}
		}
		i++;
	}

	return ple;
}

int Tauler::eliminarFiles() //Funci� per eliminar files plenes.
{
	int nEliminades = 0; //Contador de les files eliminades que retornarem.

	for (int i = 0; i < N_FILES_TAULER; i++)
	{
		bool filaPlena = true;
		int j = 1;

		while ((j < N_COL_TAULER) && (filaPlena))
		{
			if (m_tauler[i][j] == COLOR_NEGRE) //Si ja alguna posici� del tauler que estigui buida, la fila en la que es trobi no est� plena.
			{
				filaPlena = false;
			}
			else
			{
				j++;
			}
		}

		if (filaPlena) //Si la fila est� plena, es baixa la que hi ha a sobre i es buida la de dalt.
		{
			for (int y = i; y > 0; y--)
			{
				for (int x = 0; x < N_COL_TAULER; x++)
				{
					m_tauler[y][x] = m_tauler[y - 1][x]; //Baixem els valor d'una fila.
				}
			}

			for (int y = 0; y < N_COL_TAULER; y++)
			{
				m_tauler[0][y] = COLOR_NEGRE; //Indiquem que la primera fila queda buida.
			}

			nEliminades++; //S'incrementa el n�mero de files eliminades.
		}
	}

	return nEliminades;
}

void Tauler::dibuixaTauler() //Funci� per dibuixar el tauler amb les seves figures.
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false); //Dibuixem el fons.
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false); //Dibuixem el tauler.

	for (int i = 0; i < N_FILES_TAULER; i++) //Recorrem cada posici� que ocupa el tauler i el pintem amb el seu color corresponent a la posici� corresponent.
	{
		for (int j = 1; j < N_COL_TAULER; j++) //j = 1 per qu� j = 0 �s un l�mit del tauler.
		{
			if (m_tauler[i][j] != COLOR_NEGRE) //Pintem el tauler nom�s quan la casella no �s negre.
			{
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_tauler[i][j] + 1), //Color de la posici� del tauler.
					POS_X_TAULER + (j * MIDA_QUADRAT), POS_Y_TAULER + (i * MIDA_QUADRAT), false); //Posici� x i posici� y dins del tauler.
			}
		}
	}
}