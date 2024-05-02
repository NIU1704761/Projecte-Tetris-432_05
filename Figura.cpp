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
	m_x = x; //Assignem variable x a la coordenada 'x' de referència
	m_y = y; //Assignem variable y a la coordenada 'y' de referència
	m_color = (ColorFigura)figura; //Assignem al color de la figura el color associat al tipus de figura.
	m_tipus = figura; //Assignem variable figura al tipus de figura.

	ColorFigura matriu[MAX_AMPLADA][MAX_ALCADA]; //Matriu per representar la figura, inicialitzada en negre.

	for (int i = 0; i < MAX_AMPLADA; i++)
	{
		for (int j = 0; j < MAX_ALCADA; j++)
		{
			matriu[i][j] = COLOR_NEGRE; //Cada una de les posicions de la matriu que representa la figura s'inicialitza de color negre
		}
	}

	switch (figura)
	{
	case NO_FIGURA: //Tota la matriu negra.
		m_alcada = 0; //Com que no hi ha figura, l'alçada és 0.
		m_amplada = 0; //Com que no hi ha figura, l'amplada és 0.
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
	ColorFigura temp; //Valor temporal per guardar el valor d'una posició de la matriu.
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
		for (int j = i + 1; j < m_amplada; j++) //Comencem a j = i + 1 precisament per accedir als valors del voltant de la diagonal.
		{
			temp = matriu[i][j]; //Guardem un valor a 'temp'.
			matriu[i][j] = matriu[j][i]; //Intercanviem valors al llarg de la diagonal (la matriu serà idèntica a cada costat de la diagonal).
			matriu[j][i] = temp; //Assignem els valors guardats a 'temp' a una meitat de la diagonal, de manera que s'ha transposat la matriu.
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
			temp = matriu[i][j]; //Guardem un valor de la matriu figura a 'temp'.
			matriu[i][j] = matriu[i][m_amplada - 1 - j]; //Guardem el valor de la mateixa 'i' però la 'j' oposada a la posició de la figura.
			matriu[i][m_amplada - 1 - j] = temp; //Guardem el valor 'temp' a la posició de la figura a la que hem accedit abans.
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
			temp = matriu[i][j]; //Guardem el valor d'una posició de la matriu figura a 'temp'.
			matriu[i][j] = matriu[m_alcada - 1 - i][j]; //Assignem a aquesta posició el valor de la fila oposada dins de la matriu.
			matriu[m_alcada - 1 - i][j] = temp; //A aquesta última posició a la que hem accedit li assignem 'temp'.
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
	//En funció del tipus de gir, horari o antihorari, es crida a la funció corresponent.
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
			matriu[i][j] = m_figura[i][j]; //Cada valor de la matriu s'inicialitza amb el valor de m_figura a la mateixa posició.
		}
	}
}