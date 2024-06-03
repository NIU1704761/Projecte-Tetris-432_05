#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Jugador //Node de la llista de jugadors.
{
public:
    Jugador(const string& nom, int punts) : m_nom(nom), m_puntuacio(punts), m_seguent(nullptr) {} //Constructor de la classe.

    int getPunts() const { return m_puntuacio; } //Getter dels punts del jugador.
    string getNom() const { return m_nom; } //Getter del nom del jugador.
    Jugador* getSeguent() const { return m_seguent; } //Getter del node següent.
    
    void setPunts(int punts) { m_puntuacio = punts; } //Setter dels punts del jugador.
    void setNom(string& nom) { m_nom = nom; } //Setter del nom del jugador.
    void setSeguent(Jugador* seguent) { m_seguent = seguent; } //Setter del node següent.
    
private:
    string m_nom; //Nom del jugador.
    int m_puntuacio; //Puntuació del jugador.
    
    Jugador* m_seguent; //Node amb el jugador següent.

};
