#include "Jugador.h"

class LlistaJugadors //Classe per definir la llista de jugadors.
{
public:
	LlistaJugadors() : m_cap(nullptr) {} //Constructor de la classe.
	~LlistaJugadors(); //Destructor de la classe.

	void afegirJugador(const string& nom, int puntuacio); //Funció per afegir un node.
	void buidaLlista(); //Funció per buidar una llista.

	void carregarArxiu(const string& nomFitxer); //Funció per guardar la informació d'un arxiu a una llista.
	void guardarArxiu(const string& nomFitxer) const; //Funció per guardar la informació d'una llista a un arxiu.
	void imprimirLlista() const; //Funció per imprimir per pantalla la llista.	

private:
	Jugador* m_cap; //Primer node de la llista.

	void treu(); //Funció per treure un node.
	bool esBuida() const; //Funció per determinar si una llista està buida.

};