#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

#include <GL/glut.h>
//Enumeration des differentes possibilités de Choix de tris
typedef enum
{
    TRI_BULLES = 1,
    TRI_SELECTION,
    TRI_INSERTION,
    COMPARAISON
}_choix_tris;

typedef enum
{
    MENU_TRI_BULLES = 1,
    MENU_TRI_SELECTION,
    MENU_TRI_INSERTION,
    MENU_COMPARAISON,
    MENU_SCREENSHOT,
    QUITTER
}_ChoixMenu;

typedef struct Point Point;
struct Point{
    float x;
    float y;
};

typedef struct Couleur Couleur;
struct Couleur
{
    int Rouge;
    int Bleu;
    int Vert;
};

typedef struct glPoint glPoint;
struct glPoint{
    GLdouble x;
    GLdouble y;
};

#endif // STRUCTURES_H_INCLUDED
