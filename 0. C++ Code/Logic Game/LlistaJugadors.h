#include "Jugador.h"

class LlistaJugadors //Classe per definir la llista de jugadors.
{
public:
	LlistaJugadors() : m_cap(nullptr) {} //Constructor de la classe.
	~LlistaJugadors(); //Destructor de la classe.

	void afegirJugador(const string& nom, int puntuacio); //Funci� per afegir un node.
	void buidaLlista(); //Funci� per buidar una llista.

	void carregarArxiu(const string& nomFitxer); //Funci� per guardar la informaci� d'un arxiu a una llista.
	void guardarArxiu(const string& nomFitxer) const; //Funci� per guardar la informaci� d'una llista a un arxiu.
	void imprimirLlista() const; //Funci� per imprimir per pantalla la llista.	

private:
	Jugador* m_cap; //Primer node de la llista.

	void treu(); //Funci� per treure un node.
	bool esBuida() const; //Funci� per determinar si una llista est� buida.

};