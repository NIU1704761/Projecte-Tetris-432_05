#include "LlistaJugadors.h"

LlistaJugadors::~LlistaJugadors() //Destructor de la classe.
{
    Jugador* actual = m_cap; //Treballem sobre el node actual, que assignem al primer.
    while (actual != nullptr) //Mentres no sigui null.
    {
        Jugador* seguent = actual->getSeguent(); //Obtenim el seg�ent.
        delete actual; //Eliminem l'actua.
        actual = seguent; //Determinem que el seg�ent �s l'actual.
    }
}

void LlistaJugadors::afegirJugador(const string& nom, int puntuacio) //Funci� per afegir un node a la llista.
{
    Jugador* nouJugador = new Jugador(nom, puntuacio); //Declarem el nou node jugador.

    if ((!m_cap) || ((m_cap->getPunts()) < puntuacio)) //Si el nou jugador no �s el cap i la seva puntuaci� �s m�s alta que la del cap.
    {
        nouJugador->setSeguent(m_cap); //El node seg�ent al nou node �s el primer.
        m_cap = nouJugador; //El nou node �s el nou primer.
    }
    else //Si no t� la puntuaci� m�s alta.
    {
        Jugador* actual = m_cap; //Comencem pel primer element.
        while ((actual->getSeguent()) && ((actual->getSeguent()->getPunts()) >= puntuacio)) //Anem comprovant les puntuacions de la llista per poder afegir el node.
            actual = actual->getSeguent(); //Anem accedint al seg�ent node.
        nouJugador->setSeguent(actual->getSeguent()); //Assignem el node seg�ent del nou jugador.
        actual->setSeguent(nouJugador); //Assignem la posici� del nou jugador.
    }
}

void LlistaJugadors::imprimirLlista() const //Funci� per imprimir per pantalla la llista de puntuacions.
{
    Jugador* actual = m_cap; //Comencem pel primer element.
    while (actual != nullptr) //Mentres el node actual no sigui null.
    {
        cout << actual->getNom() << " " << actual->getPunts() << endl; //Mostrem el nom i la puntuaci� del jugador.
        actual = actual->getSeguent(); //Accedim al seg�ent node.
    }
}

void LlistaJugadors::carregarArxiu(const string& nomFitxer) //Funci� per guardar la informaci� d'un fitxer a una llista.
{
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open()) //Si el fitxer est� obert.
    {
        string nom; 
        int puntuacio;
        while (fitxer >> nom >> puntuacio) //Mentres hi hagi elements al fitxer.
        {
            afegirJugador(nom, puntuacio); //Afegim un jugador a la llista.
        }
        fitxer.close(); //Tanquem el fitxer.
    }
    else //Si no s'obra el fitxer, missatge d'error.
    {
        cout << "File " << nomFitxer << " not available." << endl;
    }
}

void LlistaJugadors::guardarArxiu(const string& nomFitxer) const //Funci� per guardar la informaci� d'una llista a un arxiu.
{
    ofstream fitxer(nomFitxer);
    if (fitxer.is_open())  //Si el fitxer est� obert.
    {
        Jugador* actual = m_cap; //Comencem pel primer node.
        while (actual != nullptr) //Mentres no sigui null.
        {
            fitxer << actual->getNom() << " " << actual->getPunts() << endl; //Escrivim el fitxer.
            actual = actual->getSeguent(); //Accedim al seg�ent node.
        }
        fitxer.close(); //Tanquem el fitxer.
    }
    else  //Si no es pot obrir el fitxer, missatge d'error.
    {
        cout << "File " << nomFitxer << " not available." << endl;
    }
}

bool LlistaJugadors::esBuida() const //Funci� que comprova si una llista est� buida.
{
    return m_cap == nullptr; //Retornem 1 si el primer element �s nullptr i un 0 si no.
}

void LlistaJugadors::treu() //Funci� per eliminar el primer element de la llista.
{
    if (!esBuida()) //Si la llista no est� buida.
    {
        Jugador* jugadorEliminar = m_cap; //Assignem el jugador a eliminar com a el primer element de la llista.
        m_cap = m_cap->getSeguent(); //Forcem que el primer element sigui el seg�ent.
        delete jugadorEliminar; //Eliminem l'antic primer element.
    }
    else //Si ja est� buida, missatge d'error.
        cout << "Error: Empty list." << endl;
}

void LlistaJugadors::buidaLlista() //Funci� per buidar una llista sencera.
{
    while (!esBuida()) //Mentres la llista no estigui buida, treu el primer element cada iteraci�.
        treu();
}