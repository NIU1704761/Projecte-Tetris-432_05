#include "Tetris.h"

void Tetris::mostraPuntuacions() //Funció per mostrar per pantalla les puntuacions.
{
	system("CLS"); //Buidem la pantalla.
	cout << "SCORE RANKING:" << endl;
	cout << endl;
	m_llista.carregarArxiu("./data/Games/ScoreRanking.txt"); //Accedim al fitxer i omplim la llista.
	m_llista.imprimirLlista(); //Mostrem la llista.
	m_llista.buidaLlista(); //Buidem la llista un cop mostrada.
}

void Tetris::afegeixPuntuacio(int puntuacio, const string& nom) //Funció per modificar la llista de puntuacions.
{
	m_llista.carregarArxiu("./data/Games/ScoreRanking.txt"); //Accedim al fitxer i omplim la llista.
	m_llista.afegirJugador(nom, puntuacio); //Afegim un jugador amb la informació donada.
	m_llista.guardarArxiu("./data/Games/ScoreRanking.txt"); //Traspassem la informació de la llista a l'arxiu.
	m_llista.buidaLlista(); //Buidem la llista un cop utilitzada.
}

void Tetris::mostrarPantalla(int mode, Screen& pantalla) //Funció per mostrar la partida per pantalla.
{
	PlaySound(TEXT("./data/Games/Tetris1"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //Iniciem la música.

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	do //Mentres no s'apreti la tecla ESC, fem.
	{
		//Mostrem la finestra grafica.
		pantalla.show();

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

		// Captura tots els events de ratolí i teclat de l'ultim cicle.
		pantalla.processEvents();

		if (Keyboard_GetKeyTrg(KEYBOARD_P)) //Si s'apreta la tecla "P".
		{
			if (m_pause == false) //Si pausa és fals, la posem a cert.
				m_pause = true;
			else //Si pausa és cert la posem a fals.
				m_pause = false;
		}

		if (m_pause == true) //Si pausa és cert, pausem el joc.
			m_partida.pausa();

		if (m_pause == false) //Si pausa és fals, actualitzem el joc.
			m_partida.actualitza(mode, deltaTime);

		// Actualitza la pantalla
		pantalla.update();

		if (m_partida.acabarPartida()) //Si s'acaba la partida.
		{
			do //Mentres no s'apreti la tecla ESC.
			{
				m_partida.acabarPartida(); //Acabem partida.
				PlaySound(0, 0, 0); //Parem la música.

				if (m_partida.getNivell() == 20) //Si el nivell és 20 (nivel màxim).
				{
					pantalla.update(); //Actualitzem la pantalla perquè es mostri missatge de victòria.
					PlaySound(TEXT("./data/Games/Victory"), NULL, SND_FILENAME | SND_SYNC); //Música de victòria.
					PlaySound(0, 0, 0); //Parem la música.
					m_partida.setNivell(21); //Forcem nivell 21 perquè se segueixi mostrant el missatge de victòria.
				}
				else if (m_partida.getNivell() < 20) //Si el nívell està per sota de 20.
				{
					pantalla.update(); //Actualitzem la pantalla perquè es mostri el missatge de derrota.
					PlaySound(TEXT("./data/Games/Defeat"), NULL, SND_FILENAME | SND_SYNC); //Música de derrota.
					PlaySound(0, 0, 0); //Parem la música.
					m_partida.setNivell(21); //Forcem nivell 21 perquè es segueixi mostrant el missatge de derrota.
				}

				pantalla.processEvents(); //Processem teclat per comprovar si apretem la tecla ESC.
			} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
		}
	} while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
	// Sortim del bucle si pressionem ESC

	PlaySound(0, 0, 0); //Parem qualsevol música que pugui estar sonant.
}

int Tetris::jugaNormal(Screen& pantalla) //Juguem una partida normal.
{
	m_partida.inicialitza(1, "", "", ""); //Iniciem la partida sense fitxers.

	mostrarPantalla(1, pantalla); //Iniciem la pantalla en mode normal.

	int puntuacio = m_partida.getPunts(); //Recuperem la puntuació de la partida.

	return puntuacio; //Retornem la puntuació per accedir-hi més tard.
}

void Tetris::jugaTest(Screen& pantalla) //Funció per jugar el mode test d'una partida.
{
	string partida;
	string figures;
	string moviments;
	
	//Demanem els fitxers per inicialitzar la partida i els entrem per teclat.
	cout << endl;
	cout << "Enter initialize file: "; 
	cin >> partida;
	cout << "Enter figures file: ";
	cin >> figures;
	cout << "Enter movements file: ";
	cin >> moviments;

	string path = "./data/Games/"; //Aconseguim la primera part del path per afegir-li el nom del fitxer.

	m_partida.inicialitza(2, path + partida, path + figures, path + moviments); //Inicialitzem la partida en mode test amb els fitxers pertinents.

	mostrarPantalla(2, pantalla); //Mostrem la pantalla en mode test.
}

int Tetris::juga(int mode, Screen& pantalla) //Funció per mostrar i jugar una partida.
{
	int puntuacio = 0; //Iniciem puntuació a 0.

	if (mode == 1) //Si el mode és 1 (normal).
		puntuacio = jugaNormal(pantalla); //Juguem partida normal i recuperem la puntuació.
	else if (mode == 2) //Si el mode és 2 (test).
		jugaTest(pantalla); //Juguem partida test i no necessitem la puntuació.

	return puntuacio; //Retornem la puntuació.
}

void Tetris::menu() //Funció que mostra el menú de joc.
{
	cout << "----------TETRIS----------" << endl;
	cout << "-----------MENU-----------" << endl;
	cout << "1. New Game" << endl;
	cout << "2. Test Mode" << endl;
	cout << "3. Ranking Score" << endl;
	cout << "4. Controls" << endl;
	cout << "5. Scoring" << endl;
	cout << "6. Exit" << endl;
	cout << "Type next option: ";
}

int Tetris::confirmar(int mode) //Funció per confirmar la sortida de terminal.
{
	char res;
	
	cout << "Return?(Y/N) "; //Preguntem pel retorn al menú.
	do //Mentres la resposta no sigui correcte.
	{
		cin >> res;
		if ((res == 'n') || (res == 'N')) //Si la resposta és no, sortim.
			mode = 6;
		else if ((res == 'y') || (res == 'Y')) //Si la resposta és sí, tornem al menú.
		{
			system("CLS");
			menu();
			mode = 0;
		}
		else //Si no és cap de les dues, tornem a demanar resposta.
			cout << "Answer not valid. Please retype: ";
	} while (((res != 'n') && (res != 'N')) && ((res != 'y') && (res != 'Y')));

	return mode;
}

void Tetris::controls() //Mostrem per pantalla els controls possibles.
{
	system("CLS"); //Buidem la pantalla.
	
	cout << "CONTROLS:" << endl;
	cout << endl;
	cout << "MOVE RIGHT: RIGHT ARROW" << endl;
	cout << "MOVE LEFT: LEFT ARROW" << endl;
	cout << "ROTATE RIGHT: UP ARROW" << endl;
	cout << "ROTATE LEFT: DOWN ARROW" << endl;
	cout << "SOFT DROP: C" << endl;
	cout << "HARD DROP: SPACE" << endl;
	cout << "PAUSE: P" << endl;
	cout << "EXIT: ESC" << endl;
}

void Tetris::puntuacions() //Mostrem per pantalla com es sumen les puntuacions.
{
	system("CLS"); //Buidem la pantalla.
	
	cout << "SCORE:" << endl;
	cout << endl;
	cout << "PLACE FIGURE: +10 POINTS" << endl;
	cout << "1st ROW: +100 POINTS" << endl;
	cout << "2nd ROW: +150 POINTS" << endl;
	cout << "3rd ROW: +175 POINTS" << endl;
	cout << "4th ROW: +200 POINTS" << endl;
}

int Tetris::confirmar2(int mode)
{
	char res;

	cout << endl;
	cout << "Are you sure?(Y/N) "; //Preguntem per sortir.
	do //Mentres la resposta no sigui correcte.
	{
		cin >> res;
		if ((res == 'y') || (res == 'Y')) //Si la resposta és sí, sortim.
			mode = 6;
		else if ((res == 'n') || (res == 'N')) //Si la resposta és no, tornem al menú.
		{
			system("CLS");
			menu();
			mode = 0;
		}
		else //Si no és cap de les dues, tornem a demanar resposta.
			cout << "Answer not valid. Please retype: ";
	} while (((res != 'n') && (res != 'N')) && ((res != 'y') && (res != 'Y')));

	return mode;
}

void Tetris::opcions()
{
	//Instruccions necesaries per poder incloure la llibreria i que trobi el main
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);
	
	//Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
	Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);

	string nom;
	int puntuacio;

	//Mostrem el menú per pantalla.
	cout << "----------TETRIS----------" << endl;
	cout << "-----------MENU-----------" << endl;
	cout << "1. New Game" << endl;
	cout << "2. Test Mode" << endl;
	cout << "3. Ranking Score" << endl;
	cout << "4. Controls" << endl;
	cout << "5. Scoring" << endl;
	cout << "6. Exit" << endl;
	cout << "Type option: ";

	int mode;

	do //Mentres el mode no estigui entre 1 i 6.
	{
		cin >> mode;
		switch (mode) //Plantegem tots els casos per mode.
		{
		case 1:
			puntuacio = juga(1, pantalla); //Juguem i guardem la puntuació
			cout << "Enter your initials: "; //Demanem les inicials del jugador.
			cin >> nom;
			afegeixPuntuacio(puntuacio, nom); //Afegim a la llista de puntuacions el nou jugador.
			system("CLS"); //Netegem la pantalla.
			menu(); //Mostrem el menú de nou.
			mode = 0; //Forcem el mode a 0 per tornar al do-while i no sortir.
			break;
		case 2:
			juga(2, pantalla); //Iniciem la simulació.
			system("CLS"); //Netegem la pantalla.
			menu();//Mostrem el menú de nou.
			mode = 0; //Forcem el mode a 0 per tornar al do-while i no sortir.
			break;

		case 3:
			mostraPuntuacions(); //Mostrem les puntuacions per pantalla.
			cout << endl;
			mode = confirmar(mode); //Demanem confirmació per tornar al menú o sortir.
			break;
		case 4:
			controls(); //Mostrem els controls per pantalla.
			cout << endl;
			mode = confirmar(mode); //Demanem confirmació per tornar al menú o sortir.
			break;
		case 5:
			puntuacions(); //Mostrem els tipus de punts per pantalla.
			cout << endl;
			mode = confirmar(mode); //Demanem confirmació per tornar al menú o sortir.
			break;
		case 6:
			mode = confirmar2(mode); //Assegurem la sortida de la terminal.
			break;
		default:
			cout << endl;
			cout << "Error: Option not available." << endl; //Si no és una opció possible, salta error i demanem una altra.
			cout << endl;
			cout << "Retype option: ";
			break;
		}
	} while ((mode > 6) || (mode < 1));

	//Instruccio necesaria per alliberar els recursos de la llibreria 
	SDL_Quit();
}