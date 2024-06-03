#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"

Partida::Partida() //Constructor de la classe.
{
    m_temps = 0; //Inicialitzem el temps a 0.
    m_nivell = 1; //El nivell a 1.
    m_puntuacio = 0; //La puntuació a 0.
    m_velocitat = 1.00; //La velocitat a 1 segon.

    srand(time(NULL)); //Generem una llavor per generar figures aleatories en funció de l'hora en que s'inicii la partida.
}

void Partida::inicialitzaMoviments(const string& fitxerMoviments) //Funció per inicialitzar una llista de moviments per fitxer.
{
    while (!m_moviments.esBuida()) //Mentres la llista no estigui buida, la buidem per assegurar que comencem de 0.
        m_moviments.treu();
    
    ifstream fitxer(fitxerMoviments); //Obrim el fitxer.
    if (fitxer.is_open()) //Si el fitxer està obert.
    {
        int numMoviment;
        while (fitxer >> numMoviment) //Mentres hi hagi moviments al fitxer, obtenim el moviment del fitxer i l'afegim com a node a la llista.
        {
            TipusMoviment codiMoviment = (TipusMoviment)(numMoviment);
            Moviment moviment(codiMoviment);
            m_moviments.afegeix(moviment);
        }
        fitxer.close(); //Tanquem el fitxer.
    }
}

void Partida::inicialitza(int mode, const string& fitxerInicial, const string& fitxerFigures, const string& fitxerMoviments) //Funció per inicialitzar una partida.
{
    m_nivell = 1; //Iniciem el nivell 1.
    m_puntuacio = 0; //Iniciem la puntuació a 0.
    
    if (mode == 2) //Si el mode és 2, inicialitzem per fitxer.
    {
        m_joc.inicialitzaFitxer(fitxerInicial);
        m_joc.inicialitzaFigures(fitxerFigures);
        inicialitzaMoviments(fitxerMoviments);
    }
    else if(mode == 1) //Si el mode és 1, inicialitzem normal.
        m_joc.inicialitza();
}

void Partida::puntuacio(int nElim) //Funció per definir les puntuacions.
{
    switch (nElim) //Sumem puntuacions segons el número de files eliminades. Com que "PlaySound()" només pot treballar amb una pista a la vegada, no podem afegir efectes a la partida.
    {
    case 0:
        m_puntuacio += 10;
        break;
    case 1:
        m_puntuacio += 110;
        break;
    case 2:
        m_puntuacio += 260;
        break;
    case 3:
        m_puntuacio += 385;
        break;
    case 4:
        m_puntuacio += 510;
        break;
    }

    //Determinem la velocitat i el nivell del joc en funció de la puntuació.
    if (m_puntuacio < 1000)
    {
        m_nivell = 1;
    }
    else if (m_puntuacio < 2000)
    {
        m_nivell = 2;
        m_velocitat = 0.95;
    }
    else if (m_puntuacio < 3000)
    {
        m_nivell = 3;
        m_velocitat = 0.90;
    }
    else if (m_puntuacio < 4000)
    {
        m_nivell = 4;
        m_velocitat = 0.85;
    }
    else if (m_puntuacio < 5000)
    {
        m_nivell = 5;
        m_velocitat = 0.80;
    }
    else if (m_puntuacio < 6000)
    {
        m_nivell = 6;
        m_velocitat = 0.75;
    }
    else if (m_puntuacio < 7000)
    {
        m_nivell = 7;
        m_velocitat = 0.70;
    }
    else if (m_puntuacio < 8000)
    {
        m_nivell = 8;
        m_velocitat = 0.65;
    }
    else if (m_puntuacio < 9000)
    {
        m_nivell = 9;
        m_velocitat = 0.60;
    }
    else if (m_puntuacio < 10000)
    {
        m_nivell = 10;
        m_velocitat = 0.55;
    }
    else if (m_puntuacio < 11000)
    {
        m_nivell = 11;
        m_velocitat = 0.50;
    }
    else if (m_puntuacio < 12000)
    {
        m_nivell = 12;
        m_velocitat = 0.45;
    }
    else if (m_puntuacio < 13000)
    {
        m_nivell = 13;
        m_velocitat = 0.40;
    }
    else if (m_puntuacio < 14000)
    {
        m_nivell = 14;
        m_velocitat = 0.35;
    }
    else if (m_puntuacio < 15000)
    {
        m_nivell = 15;
        m_velocitat = 0.30;
    }
    else if (m_puntuacio < 16000)
    {
        m_nivell = 16;
        m_velocitat = 0.25;
    }
    else if (m_puntuacio < 17000)
    {
        m_nivell = 17;
        m_velocitat = 0.20;
    }
    else if (m_puntuacio < 18000)
    {
        m_nivell = 18;
        m_velocitat = 0.15;
    }
    else if (m_puntuacio < 19000)
    {
        m_nivell = 19;
        m_velocitat = 0.10;
    }
    else
    {
        m_nivell = 20;
        m_velocitat = 0.05;
    }
}

bool Partida::acabarPartida() //Funció que dibuixa el final de la partida.
{
    bool acabar = m_joc.acabarJoc();

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    if (m_nivell == 20) //Si el nivell és 20, guanyem.
    {
        string msg = "HIGHEST SCORE: GAME WON!!!";
        GraphicManager::getInstance()->drawFont(FONT_GREEN_30, POS_X_TAULER - 0, POS_Y_TAULER + 200, 1.0, msg);
        string msg1 = "SCORE: " + to_string(m_puntuacio);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 125, POS_Y_TAULER + 250, 1.0, msg1);
    }
    else //Si el nivell no és 20, perdem.
    {
        string msg = "GAME OVER";
        GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER + 75, POS_Y_TAULER + 200, 1.5, msg);
        string msg2 = "SCORE: " + to_string(m_puntuacio);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 125, POS_Y_TAULER + 275, 1.0, msg2);
    }

    string sortir = "Press 'ESC' to return to menu.";
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 120, POS_Y_TAULER + 500, 0.5, sortir); //Missatge per sortir

    return acabar; //Retornem si s'ha acabat la partida.
}

void Partida::pausa() //Funció que dibuixa la pantalla de pausa.
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    string msg = "PAUSE";
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 175, POS_Y_TAULER + 200, 1.0, msg);

    string sortir = "Press 'ESC' to return to menu.";
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 120, POS_Y_TAULER + 525, 0.5, sortir); //Missatge per sortir
    string pausa = "Press 'P' to return to game.";
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 126, POS_Y_TAULER + 500, 0.5, pausa); //Missatge per tornar a la partida.
}

void Partida::actualitzaJoc(double deltaTime) //Funció que actualitza el mode joc.
{
    int nElim; //Númeno de files eliminades.

    if (m_joc.acabarJoc()) //Si s'acaba el joc, acabem la partida.     
        acabarPartida();
    else //Si no s'acaba el joc.
    {
        m_joc.dibuixaJoc(); //Dibuixem la situació.

        m_temps += deltaTime; //Considerem el temps.
        if (m_temps > m_velocitat) //Anem baixant la figura cada segon.
        {
            nElim = m_joc.baixaFigura(1); //Obtenim el número de files eliminades.
            if (m_joc.getY() == 0) //Si s'ha generat una nova figura després de baixar.
                puntuacio(nElim); //Sumem la puntuació corresponent.
            m_temps = 0.0; //Resetegem el temps.
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_C)) //Si apretem la tecla "C" baixem la figura manualment.
        {
            nElim = m_joc.baixaFigura(1); //Obtenim el número de files eliminades.
            if (m_joc.getY() == 0) //Si s'ha generat una nova figura després de baixar.
                puntuacio(nElim); //Sumem la puntuació corresponent.
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_SPACE)) //Si apretem la tecla "ESPAI" baixem la figura de cop.
        {
            nElim = m_joc.baixaFigura2(1); //Obtenim el número de files eliminades.
            puntuacio(nElim); //Sumem la puntuació corresponent.
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT)) //Si apretem la tecla "DRETA" ens movem a la dreta.
        {
            m_joc.mouFigura(1); //Movem la figura.
            m_joc.baixaFantasma(); //Actualitzem el fantasma.
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_LEFT)) //Si apretem la tecla "ESQUERRA" ens movem a l'esquerra.
        {
            m_joc.mouFigura(-1); //Movem la figura.
            m_joc.baixaFantasma(); //Actualitzem el fantasma.
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_UP)) //Si apretem la tecla "AMUNT" girem en sentit horari.
        {
            m_joc.giraFigura(GIR_HORARI); //Girem la figura.
            m_joc.baixaFantasma(); //Actualitzem el fantasma.
        }

        if (Keyboard_GetKeyTrg(KEYBOARD_DOWN)) //Si apretem la tecla "AVALL" girem en sentit antihorari.
        {
            m_joc.giraFigura(GIR_ANTI_HORARI); //Girem la figura.
            m_joc.baixaFantasma(); //Actualitzem el fantasma.
        }

        string msg = "Level: " + to_string(m_nivell) + " Score: " + to_string(m_puntuacio); //Pintem la puntuació i el nivell.
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 0.75, msg);


        string next = "Next:";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 350, POS_Y_TAULER - 35, 0.75, next);
    }
}

void Partida::actualitzaFitxer(double deltaTime)
{
    int nElim; // Comptador de files eliminades
    if (m_joc.acabarJoc())
        acabarPartida();
    else
    {
        m_joc.dibuixaJoc(); // Dibuixa la partida

        m_temps += deltaTime;
        if (m_temps > 1.0) //Fem un moviment per segon.
        {
            if (!m_moviments.esBuida()) //Si la llista de moviments no està buida.
            {
                TipusMoviment movimentActual = m_moviments.getPrimer().getMoviment(); //Obtenim el primer moviment.

                switch (movimentActual) //En funció del moviment.
                {
                case MOVIMENT_BAIXA_FINAL: // Prem l'espai del teclat
                    nElim = m_joc.baixaFigura2(2); // Guarda les files eliminades
                    puntuacio(nElim); // Suma la puntuacio per col·locar una figura de cop
                    break;

                case MOVIMENT_DRETA: // Prem la fletxa dreta del teclat
                    m_joc.mouFigura(1); // Mou la figura cap a la dreta
                    break;

                case MOVIMENT_ESQUERRA: // Prem la fletxa esquerra del teclat
                    m_joc.mouFigura(-1); // Mou la figura cap a l'esquerra
                    break;

                case MOVIMENT_GIR_HORARI: // Prem la fletxa amunt del teclat
                    m_joc.giraFigura(GIR_HORARI); // Gira la figura en sentit horari
                    break;

                case MOVIMENT_GIR_ANTIHORARI: // Prem la fletxa avall del teclat
                    m_joc.giraFigura(GIR_ANTI_HORARI); // Gira la figura en sentit antihorari
                    break;

                case MOVIMENT_BAIXA: // Prem la c del teclat
                    nElim = m_joc.baixaFigura(2); // Baixa la figura
                    if (m_joc.getY() == 0)
                        puntuacio(nElim);
                    break;

                default:
                    break;
                }

                m_moviments.treu(); // Treu el moviment processat
            }

            m_temps = 0.0; //Resetegem el temps.
        }

        std::string msg = "Level: " + std::to_string(m_nivell) + " Score: " + std::to_string(m_puntuacio);
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 0.75, msg);
    }
}

void Partida::actualitza(int mode, double deltaTime) //Funció que actualitza la partida.
{
    if (mode == 1) //Si estem en mode normal.
        actualitzaJoc(deltaTime);
    else if (mode == 2) //Si estem en mode test.
        actualitzaFitxer(deltaTime);
}