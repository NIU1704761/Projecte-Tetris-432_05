#include "Figura.h"

Figura::Figura() //Inicialitzem totes les variables privades de Figura a 0.
{
	m_x = 0;
	m_y = 0;
	m_color = NO_COLOR;
	m_tipus = NO_FIGURA;
	m_amplada = 0;
	m_alcada = 0;

	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			m_figura[i][j] = m_color;
		}
	}
}

void Figura::inicialitza(TipusFigura figura, int x, int y) //Inicialitzem cada figura.
{
	m_x = x;
	m_y = y;
	m_color = (ColorFigura)figura;
	m_tipus = figura;

	ColorFigura matriu[MAX_AMPLADA][MAX_ALCADA]; //Matriu per representar la figura, inicialitzada en no color.

	for (int i = 0; i < MAX_AMPLADA; i++)
	{
		for (int j = 0; j < MAX_ALCADA; j++)
		{
			matriu[i][j] = NO_COLOR;
		}
	}

	switch (figura)
	{
	case NO_FIGURA: //Tota la matriu negre.
		m_alcada = 0;
		m_amplada = 0;
		break;
	case FIGURA_O: //Representar la figura en 2x2
		m_amplada = 2;
		m_alcada = 2;

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				matriu[i][j] = COLOR_GROC;
		break;
	case FIGURA_I: //Representar la figura en 1x4
		m_amplada = 4;
		m_alcada = 4;

		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			matriu[1][j] = COLOR_BLAUCEL;
		}
		break;
	case FIGURA_T: //Representar la figura
		m_amplada = 3;
		m_alcada = 3;

		for (int j = 0; j < 3; j++)
		{
			matriu[1][j] = COLOR_MAGENTA;
		}
		matriu[0][1] = COLOR_MAGENTA;
		break;
	case FIGURA_L: //Representar la figura
		m_amplada = 3;
		m_alcada = 3;

		for (int j = 0; j < 3; j++)
		{
			matriu[1][j] = COLOR_TARONJA;
		}
		matriu[0][2] = COLOR_TARONJA;
		break;
	case FIGURA_J: //Representar la figura
		m_amplada = 3;
		m_alcada = 3;

		for (int j = 0; j < 3; j++)
		{
			matriu[1][j] = COLOR_BLAUFOSC;
		}
		matriu[0][0] = COLOR_BLAUFOSC;
		break;
	case FIGURA_Z: //Representar la figura
		m_amplada = 3;
		m_alcada = 3;

		matriu[0][0] = COLOR_VERMELL;
		matriu[0][1] = COLOR_VERMELL;
		matriu[1][1] = COLOR_VERMELL;
		matriu[1][2] = COLOR_VERMELL;
		break;
	case FIGURA_S: //Representar la figura
		m_amplada = 3;
		m_alcada = 3;

		matriu[0][1] = COLOR_VERD;
		matriu[0][2] = COLOR_VERD;
		matriu[1][0] = COLOR_VERD;
		matriu[1][1] = COLOR_VERD;
		break;
	}

	for (int i = 0; i < MAX_AMPLADA; i++)
	{
		for (int j = 0; j < MAX_ALCADA; j++)
		{
			m_figura[i][j] = matriu[i][j]; //Assigna la matriu que hem creat a la variable privada m_figura.
		}
	}
}

void Figura::transposarMatriu() //Funci� per transposar una matriu.
{
	ColorFigura temp;
	ColorFigura matriu[MAX_ALCADA][MAX_AMPLADA];

	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			matriu[i][j] = m_figura[i][j]; //Assegurem que la matriu que anem a modificar sigui la de la figura.
		}
	}

	for (int i = 0; i < m_alcada; i++) // Intercanviar files per columnes 1 cop.
	{
		for (int j = i + 1; j < m_amplada; j++)
		{
			temp = matriu[i][j];
			matriu[i][j] = matriu[j][i];
			matriu[j][i] = temp;
		}
	}

	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			m_figura[i][j] = matriu[i][j]; // Figura amb la matriu transposada (encara no est� girada).
		}
	}
}

void Figura::girHorari() //Funci� que defineix el gir horari de la figura.
{
	transposarMatriu(); //Primer es transposa la matriu.

	ColorFigura matriu[MAX_AMPLADA][MAX_ALCADA];
	for (int i = 0; i < MAX_AMPLADA; i++)
	{
		for (int j = 0; j < MAX_ALCADA; j++)
		{
			matriu[i][j] = m_figura[i][j]; //Assegurem que la matriu que anem a modificar sigui la de la figura ja transposada.
		}
	}

	ColorFigura temp;

	for (int i = 0; i < m_alcada; i++)
	{
		int meitat = m_amplada / 2;
		for (int j = 0; j < meitat; j++) // Intercanviem columnes �nicament un cop (no fas el recorregut sencer per no retornar la matriu original).
		{
			temp = matriu[i][j];
			matriu[i][j] = matriu[i][m_amplada - 1 - j];
			matriu[i][m_amplada - 1 - j] = temp;
		}
	}

	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			m_figura[i][j] = matriu[i][j]; // Figura amb la matriu girada.
		}
	}
}

void Figura::girAntihorari() //Funci� que defineix el gir antihorari de la figura.
{
	transposarMatriu(); //Primer es transposa la matriu.

	ColorFigura matriu[MAX_AMPLADA][MAX_ALCADA];
	for (int i = 0; i < MAX_AMPLADA; i++)
	{
		for (int j = 0; j < MAX_ALCADA; j++)
		{
			matriu[i][j] = m_figura[i][j]; //Assegurem que la matriu que anem a modificar sigui la de la figura ja transposada.
		}
	}

	ColorFigura temp;

	for (int j = 0; j < m_amplada; j++)
	{
		int meitat = m_alcada / 2;
		for (int i = 0; i < meitat; i++) // Intercanviem files �nicament un cop (no fas el recorregut sencer per no retornar la matriu original).
		{
			temp = matriu[i][j];
			matriu[i][j] = matriu[m_alcada - 1 - i][j];
			matriu[m_alcada - 1 - i][j] = temp;
		}
	}

	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			m_figura[i][j] = matriu[i][j]; // Figura amb la matriu girada.
		}
	}
}

void Figura::girar(DireccioGir gir) //Funci� que implementa els dos tipus de girs.
{

	if (gir == GIR_HORARI)
	{
		girHorari();
	}
	else
	{
		girAntihorari();
	}
}

void Figura::getMatriu(ColorFigura matriu[MAX_ALCADA][MAX_AMPLADA]) const //Funci� que recupera la matriu que representa la figura.
{
	for (int i = 0; i < MAX_ALCADA; i++)
	{
		for (int j = 0; j < MAX_AMPLADA; j++)
		{
			matriu[i][j] = m_figura[i][j];
		}
	}
}

void Figura::dibuixaFigura() const //Funci� per dibuixar una figura.
{ 	
	for (int i = 0; i < m_alcada; i++) //Recorrem cada posici� que ocupa la figura i la pintem amb el seu color corresponent a la posici� corresponent.
	{
		for (int j = 0; j < m_amplada; j++)
		{
			if (m_figura[i][j] != NO_COLOR) //Per totes les posicions de la figura que siguin de colors.
			{
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_figura[i][j] + 1), //Color de la figura.
					POS_X_TAULER + ((m_x + j) * MIDA_QUADRAT), POS_Y_TAULER + ((m_y + i) * MIDA_QUADRAT), false); //Posici� x i posici� y.
			}
		}
	}
}

int Figura::Aleatori(int NumMax) //Funci� per generar un n�mero aleatori.
{
	int NumAleatori;
	
	if (NumMax != 0)
		NumAleatori = rand() % NumMax + 1; //Generem un n�mero aleatori per determinar la figura seg�ent.
	else
		NumAleatori = 2 + rand() % 7; //Generem un n�mero aleatori per determinar lo posici� x en la que es generar� la figura.

	return NumAleatori; //Retornem el n�mero aleatori.
}

void Figura::figuraAleatoria()
{
	inicialitza((TipusFigura)Aleatori(7), Aleatori(0), 0); //Inicialitzem la figura aleatoria.

	for (int i = 0; i < Aleatori(3); i++)
	{
		girar(GIR_HORARI); //Girem la figura aleatori un n�mero aleatori de vegades.
	}
}

void Figura::dibuixaSeguent() const
{
	for (int i = 0; i < m_alcada; i++) //Recorrem cada posici� que ocupa la figura i la pintem amb el seu color corresponent a la posici� corresponent.
	{
		for (int j = 0; j < m_amplada; j++)
		{
			if (m_figura[i][j] != NO_COLOR)
			{
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_figura[i][j] + 1), //Color de la figura.
					POS_X_TAULER + ((15 + j) * MIDA_QUADRAT), POS_Y_TAULER + ((i) * MIDA_QUADRAT), false); //Posici� x i posici� y.
			}
		}
	}
}

void Figura::dibuixaSeguent2() const
{
	for (int i = 0; i < m_alcada; i++) //Recorrem cada posici� que ocupa la figura i la pintem amb el seu color corresponent a la posici� corresponent.
	{
		for (int j = 0; j < m_amplada; j++)
		{
			if (m_figura[i][j] != NO_COLOR)
			{
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_figura[i][j] + 1), //Color de la figura.
					POS_X_TAULER + ((15 + j) * MIDA_QUADRAT), POS_Y_TAULER + ((5 + i) * MIDA_QUADRAT), false); //Posici� x i posici� y.
			}
		}
	}
}

void Figura::dibuixaSeguent3() const
{
	for (int i = 0; i < m_alcada; i++) //Recorrem cada posici� que ocupa la figura i la pintem amb el seu color corresponent a la posici� corresponent.
	{
		for (int j = 0; j < m_amplada; j++)
		{
			if (m_figura[i][j] != NO_COLOR)
			{
				GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(m_figura[i][j] + 1), //Color de la figura.
					POS_X_TAULER + ((15 + j) * MIDA_QUADRAT), POS_Y_TAULER + ((10 + i) * MIDA_QUADRAT), false); //Posici� x i posici� y.
			}
		}
	}
}

void Figura::dibuixaFantasma() const
{
	for (int i = 0; i < m_alcada; i++) //Recorrem cada posici� que ocupa la figura i la pintem amb el seu color corresponent a la posici� corresponent.
	{
		for (int j = 0; j < m_amplada; j++)
		{
			if (m_figura[i][j] != NO_COLOR)
			{
				GraphicManager::getInstance()->drawSprite(GRAFIC_QUADRAT_GRIS, //Color de la figura.
					POS_X_TAULER + ((m_x + j) * MIDA_QUADRAT), POS_Y_TAULER + ((m_y + i) * MIDA_QUADRAT), false); //Posici� x i posici� y.
			}
		}
	}
}