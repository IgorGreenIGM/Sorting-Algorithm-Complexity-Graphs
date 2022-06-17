#ifndef DRAWER_H_INCLUDED
#define DRAWER_H_INCLUDED

extern double echelle_x, echelle_y;     //Variables d'echelle

void DessinerDrawerAnimated(Point *drawer, Point *pointA, Point *pointB, Couleur *couleur);

void DessinTris(int Choix);

void DessinTrisAnimated(int choix);

#endif // DRAWER_H_INCLUDED
