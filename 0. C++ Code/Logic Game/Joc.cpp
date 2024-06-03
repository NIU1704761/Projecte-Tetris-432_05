#include "Joc.h"

void Joc::inicialitza() //Funció per inicialitzar el joc.
{
	for (int i = 0; i < N_FILES_TAULER; i++)
		for (int j = 0; j < N_COL_TAULER; j++)
			m_tauler.setCasella(COLOR_NEGRE, i, j); //Per cada casella del tauler, la inicialitzem negre.
	
	m_figura.figuraAleatoria(); //Generem la figura amb la que jugarem.

	m_figuraSeguent.figuraAleatoria(); //Generem la figura següent.
	m_figuraSeguent2.figuraAleatoria(); //Generem la figura següent.
	m_figuraSeguent3.figuraAleatoria(); //Generem la figura següent.

	baixaFantasma(); //Baixem la figura fantasma.
}

void Joc::buidarPantalla()
{
	for (int i = 0; i < N_FILES_TAULER; i++)
		for (int j = 0; j < N_COL_TAULER; j++)
			m_tauler.setCasella(COLOR_NEGRE, i, j); //Per cada casella del tauler, la inicialitzem negre.

	m_figura.inicialitza(NO_FIGURA, 0, 0); //Eliminem la figura amb la que juguem.
	m_figuraSeguent = m_figura; //Eliminem figura.
	m_figuraSeguent2 = m_figura; //Eliminem figura.
	m_figuraSeguent3 = m_figura; //Eliminem figura.
	m_fantasma = m_figura; //Eliminem figura.
}

void Joc::inicialitzaFitxer(const string& nomFitxer) //Inicialitzem la situació de joc segons una informació d'un fitxer.
{	
	buidarPantalla(); //Buidem la pantalla anterior.
	
	ifstream fitxer;
	fitxer.open(nomFitxer); //Obrim el fitxer.

	if (fitxer.is_open())
	{
		int tipus, fila, columna, nGirs;

		fitxer >> tipus >> fila >> columna >> nGirs; //Llegim el fitxer i assignem la informació de la figura.

		m_figura.setX(columna - 1); //Assignem la coordenada 'x' de referència de la figura.
		m_figura.setY(fila - 1); //Assignem la coordenada 'y' de referència de la figura.
		m_figura.inicialitza((TipusFigura)tipus, columna, fila - 1); //Inicialitzem la figura per saber quina forma té.

		for (int i = 0; i < nGirs; i++) //Girar en sentit horari la figura tants cops com indici el document a nGirs.
		{
			m_figura.girar(GIR_HORARI);
		}

		int casella;
		for (int i = 0; i < N_FILES_TAULER; i++)
		{
			for (int j = 1; j < N_COL_TAULER; j++)
			{
				fitxer >> casella;
				m_tauler.setCasella((ColorFigura)(casella), i, j); //Assignem cada posició del tauler amb la informació del fitxer.
			}
		}

	}

	fitxer.close(); //Tanquem el fitxer.
}

int Joc::baixaFigura2(int mode)
{
	int nElim = 0;
	bool noBaixa = false;
	int i = m_figura.getY();

	Figura temp = m_figura; //Creem una figura temporal per comprobar si pot baixar.

	while ((i < N_FILES_TAULER) && (!noBaixa))
	{
		temp.baixar(); //La baixem.
		noBaixa = m_tauler.colisiona(temp); //Comprovem si colisiona.
		if (!noBaixa)
			i++; //Si pot baixar, la intentem baixar una fila més.
	}

	ColorFigura copiaFigura[MAX_ALCADA][MAX_AMPLADA];
	m_figura.getMatriu(copiaFigura);
	int x, y, amplada, alcada;

	x = m_figura.getX();
	y = i;
	amplada = m_figura.getAmplada();
	alcada = m_figura.getAlcada();

	for (int i = 0; i < alcada; i++)
	{
		for (int j = 0; j < amplada; j++)
		{
			if (copiaFigura[i][j] != NO_COLOR)
			{
				m_tauler.setCasella(copiaFigura[i][j], y + i, x + j); //Quan colisiona, la col·loquem dins del tauler a la posició en la que s'ha quedat.
			}
		}
	}

	nElim = m_tauler.eliminarFiles(); //Comprovem les files eliminades. 
	
	acabarMoviment(mode); //Acabem el moviment.
	
	return nElim; //Retornem el número de files eliminades.
}

int Joc::baixaFigura(int mode) //Funció per baixar la figura.
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
				if (copiaFigura[i][j] != NO_COLOR)
				{
					m_tauler.setCasella(copiaFigura[i][j], y + i, x + j); //Si colisiona, la col·loquem dins del tauler a la posició en la que s'ha quedat.
				}
			}
		}

		nElim = m_tauler.eliminarFiles(); //Comprovem les files eliminades. 

		acabarMoviment(mode); //Acabem el moviment.
	}

	return nElim; //Retornem el número de files eliminades.
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

bool Joc::giraFigura(const DireccioGir& direccio) //Funció per girar una figura.
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

void Joc::dibuixaJoc() //Funció per dibuixar el joc.
{
	m_tauler.dibuixaTauler(); //Dibuixem el tauler.

	m_fantasma.dibuixaFantasma(); //Dibuixem el fantasma perquè no colapsi amb la figura.
	m_figura.dibuixaFigura(); //Dibuixem la figura.

	m_figuraSeguent.dibuixaSeguent(); //Dibuixem la figura següent.
	m_figuraSeguent2.dibuixaSeguent2(); //Dibuixem la figura següent.
	m_figuraSeguent3.dibuixaSeguent3(); //Dibuixem la figura següent.
}

bool Joc::acabarJoc() //Funció per acabar el joc.
{
	bool acabar = m_tauler.taulerPle(m_figura); //Comprovem que el tauler estigui ple.
	if (acabar)
	{
		m_figura.inicialitza(NO_FIGURA, 0, 0); //Eliminem figura.
		m_figuraSeguent = m_figura; //Eliminem figura.
		m_figuraSeguent2 = m_figura; //Eliminem figura.
		m_figuraSeguent3 = m_figura; //Eliminem figura.
		m_fantasma = m_figura; //Eliminem figura.
	}

	return acabar; //Retornem si s'ha acabat la partida o no.
}

void Joc::inicialitzaFigures(const string& fitxerFigures) //Funció per inicialitzar una cua de figures.
{
	while (!m_figures.esBuida()) //Mentres la cua no estigui buida.
		m_figures.treu(); //Eliminem el primer element de la cua per assegurar-nos que estigui buida.
	
	int codi, fila, columna, gir;

	ifstream fitxer;
	fitxer.open(fitxerFigures); //Obrim el fitxer.
	if (fitxer.is_open()) //Si el fitxer esta obert.
	{
		while (fitxer >> codi >> fila >> columna >> gir)
		{
			TipusFigura codiFig = (TipusFigura)(codi);
			Figures figura(codiFig, fila, columna, gir); //Inicialitzem un node amb la informació del fitxer.
			m_figures.afegeix(figura); //Afegim el node a la cua de figures.
		}
		fitxer.close(); //Tanquem el fitxer.
	}
}

void Joc::baixaFantasma() //Funció per determinar el moviment de la figura fantasma.
{
	m_fantasma = m_figura; //Fantasma igual a figura.
	bool noBaixa = false;
	int i = m_fantasma.getY(); 

	Figura temp = m_fantasma; //Creem una figura temporal per comprobar si pot baixar.

	while ((i < N_FILES_TAULER) && (!noBaixa))
	{
		temp.baixar(); //La baixem.
		noBaixa = m_tauler.colisiona(temp); //Comprovem si colisiona.
		if (!noBaixa)
			i++; //Si pot seguir baixant, seguim baixant.
	}

	m_fantasma.setY(i); //Assignem a la figura fantasma la coordenada Y.
	m_fantasma.setColor(COLOR_GRIS); //La pintem de color gris.
}

void Joc::acabarMoviment(int mode)
{
	if (mode == 1) //Si estem en el mode normal de joc.
	{
		m_figura = m_figuraSeguent; //La nova figura serà la figura següent.
		m_figuraSeguent = m_figuraSeguent2; //Assignem la següent figura.
		m_figuraSeguent2 = m_figuraSeguent3; //Assignem la següent figura.
		m_figuraSeguent3.figuraAleatoria(); //Generem la següent figura. 
		baixaFantasma(); //Baixem la figura fantasma.
	}
	else if (mode == 2) //Si estem al mode test
	{
		if (!m_figures.esBuida()) //Si la llista de figures no és buida.
		{
			Figures figura = m_figures.getPrimer(); //Obtenim la primera figura de la cua.
			int girs = m_figures.getPrimer().getGir(); //Obtenim el número de girs necessaris.

			m_figura.inicialitza(figura.getTipus(), figura.getColumna(), figura.getFila()); //Inicialitzem la figura.

			for (int i = 0; i < girs; i++)
				m_figura.girar(GIR_HORARI); //Girem la figura.

			m_figures.treu(); //Treiem de la cua la primera posició.
		}
		else //Si la cua està buida.
			m_figura.inicialitza(NO_FIGURA, 0, 0); //Inicialitzem no figura.
	}
}