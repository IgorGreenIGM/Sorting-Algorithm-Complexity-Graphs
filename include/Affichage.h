#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include "../include/Structures.h"

void Affichage();

void afficher_axes();

void PrintTexte(float x, float y, float z, char *chaine, void *font);

void DessinTexteTris(int choix);

void DessinBoxTexteTris(int choix, Couleur *couleur);

#endif // AFFICHAGE_H_INCLUDED
