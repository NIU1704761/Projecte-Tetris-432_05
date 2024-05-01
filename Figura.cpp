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

void Figura::inicilitza(TipusFigura figura, int x, int y) //Inicialitzem cada figura.
{
	m_x = x;
	m_y = y;
	m_color = (ColorFigura)figura;
	m_tipus = figura;

	ColorFigura matriu[MAX_AMPLADA][MAX_ALCADA]; //Matriu per representar la figura, inicialitzada en negre.

	for (int i = 0; i < MAX_AMPLADA; i++)
	{
		for (int j = 0; j < MAX_ALCADA; j++)
		{
			matriu[i][j] = COLOR_NEGRE;
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

void Figura::transposarMatriu() //Funció per transposar una matriu.
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
			m_figura[i][j] = matriu[i][j]; // Figura amb la matriu transposada (encara no està girada).
		}
	}
}

void Figura::girHorari() //Funció que defineix el gir horari de la figura.
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
		for (int j = 0; j < meitat; j++) // Intercanviem columnes únicament un cop (no fas el recorregut sencer per no retornar la matriu original).
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

void Figura::girAntihorari() //Funció que defineix el gir antihorari de la figura.
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
		for (int i = 0; i < meitat; i++) // Intercanviem files únicament un cop (no fas el recorregut sencer per no retornar la matriu original).
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

void Figura::girar(DireccioGir gir) //Funció que implementa els dos tipus de girs.
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

void Figura::getMatriu(ColorFigura matriu[MAX_ALCADA][MAX_AMPLADA]) const //Funció que recupera la matriu que representa la figura.
{
	for (int i = 0; i < m_alcada; i++)
	{
		for (int j = 0; j < m_amplada; j++)
		{
			matriu[i][j] = m_figura[i][j];
		}
	}
}