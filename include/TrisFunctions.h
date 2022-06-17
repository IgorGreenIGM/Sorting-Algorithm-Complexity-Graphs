#ifndef TRISFUNCTIONS_H_INCLUDED
#define TRISFUNCTIONS_H_INCLUDED

#include <GL/gl.h>

void remplir_tableau(int tableau[], int taille, int maximum);

void tri_Bulles(int *tableau, int fin);
void triSelection(int *tableau,int taille);
void triInsertion(int *tableau, int taille);

void glDoubleTriInsertion(GLdouble *tableau, int taille);

void copier_tableau(int *tableauD, int *tableauS, int fin);

double Calcultemps(int *tableau, int choix, int fin);

#endif
