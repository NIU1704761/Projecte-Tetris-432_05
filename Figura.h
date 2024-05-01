#ifndef FIGURA_H
#define FIGURA_H



typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;


typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S,
} TipusFigura;

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

class Figura
{
public:
    Figura(); //Constructor de Figura per inicialitzar-la a 0.
    void setX(int x) { m_x = x; } //Setter de la variable m_x.
    void setY(int y) { m_y = y; } //Setter de la variable m_y.
    int getX() { return m_x; } //Getter de la variable m_x. 
    int getY() { return m_y; } //Getter de la variable m_y.
    int getAmplada() { return m_amplada; } //Getter de la variable m_amplada.
    int getAlcada() { return m_alcada; } //Getter de la variable m_alcada.
    void getMatriu(ColorFigura matriu[MAX_ALCADA][MAX_AMPLADA]) const; //Getter de la matriu m_figura.
    void inicilitza(TipusFigura figura, int x, int y); //Funció per inicilitzar la matriu de la figura.
    void movimentHoritzontal(int dirX) { m_x += dirX; } //Funció per determinar el moviment horitzontal de la figura.
    void baixar() { m_y++; } //Funció per determinar la baixada de la figura.
    void girar(DireccioGir gir); //Funció per determinar el gir de la figura.
    

private:
    ColorFigura m_color; //Variable per guardar el color de la figura.
    TipusFigura m_tipus; //Variable per guardar el tipus de figura.
    int m_x; //Variable per guardar la coordenada 'x' de la posició de referència de la matriu.
    int m_y; //Variable per guardar la coordenada 'y' de la posició de referència de la matriu.
    int m_amplada; //Variable per guardar l'amplada real de la figura.
    int m_alcada; //Variable per guardar l'alçada real de la figura.
    ColorFigura m_figura[MAX_AMPLADA][MAX_ALCADA]; //Variable de tipus ColorFigura on es guarda la figura en forma de matriu.
    void transposarMatriu(); //Funció per transposar matrius.
    void girHorari(); //Funció que defineix el gir horari d'una figura.
    void girAntihorari(); //Funció que defineix el gir anti-horari d'una figura.
};


#endif
