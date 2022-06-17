
/** \brief Fonction de dessin de la ProgressBar, elle se dessine sur un background, un rectangle blanc en l'occurence
 * \constantes la marge de dessin de la barre de progression par rapport au background(side_margin et topDown_margin)
 * \param la hauteur de la barre, la largeur de la barre
 * \return Rien.
 */

#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Affichage.h"
#include "../include/Structures.h"

//Fonction d'Affichage du pourcentage d'avancement (texte)
void AfficherTexteLoadBarStatus(int etat, int maximum, float x, float y)
{
    char *buff = (char*)malloc(8*sizeof(char));
    itoa(100*etat/maximum, buff, 10);
    strcat(buff, "%");
    glColor3ub(0, 0, 0);
    PrintTexte(x, y, 0, buff, GLUT_BITMAP_HELVETICA_12);
    free(buff);
    glFlush();
}

//Fonction de dessin du background de la progressBar
void DrawProgressBarBackground(double largeurBar, double hauteurBar, double side_margin, double topDown_margin)
{
    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2d(9-largeurBar-side_margin, 9+hauteurBar);
    glVertex2d(9+largeurBar, 9+hauteurBar);
    glVertex2d(9+largeurBar, 9-hauteurBar);
    glVertex2d(9-largeurBar-side_margin, 9-hauteurBar);
    glEnd();
}

/*  fonction de dessin de la progression:
    il s'agit ici de dessiner un rectangle en fonction de la positionActuelle
    le Maximum designe la valeur maximale du tableau, et l'echelle designe la largeur de la barre divisé par le maximum du tableau
    Max peut etre remplacé par une valeur maximale quelconque, pour possible reutilisation du code
    la positionActuelle est donnée par le produit de l'etat actuelle par echelle
    A 100%, la valeur de la positionActuelle est egale à l'echelle. Consulter "FichierStockage.cpp"
    La valeur 9 depend du repere prédéini, lire Le main.cpp
*/
void DrawProgressBar(int etat, int maximum, long double echelle, double largeurBar, double hauteurBar, double side_margin, double topDown_margin)
{
    double positionActuelle = (double)etat*echelle;

    glBegin(GL_QUADS);
    glColor3ub(0, 128, 0);
    glVertex2d((9-largeurBar+side_margin), (9+hauteurBar-topDown_margin));
    glVertex2d((9-largeurBar-side_margin+(2*positionActuelle)), (9+hauteurBar-topDown_margin));
    glVertex2d((9-largeurBar-side_margin+(2*positionActuelle)), (9-hauteurBar+topDown_margin));
    glVertex2d((9-largeurBar+side_margin), (9-hauteurBar+topDown_margin));
    glEnd();
    glFlush();

    AfficherTexteLoadBarStatus(etat, maximum, 9, 9);
}

//Fonction d'effacement de la progressBar
//L'effacement designe juste l'affichage d'un rectangle Noir à la place de la progressBar
void CLearProgressBar(double largeurBar, double hauteurBar, double side_margin, double topDown_margin)
{
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2d(9-largeurBar-side_margin, 9+hauteurBar);
    glVertex2d(9+largeurBar, 9+hauteurBar);
    glVertex2d(9+largeurBar, 9-hauteurBar);
    glVertex2d(9-largeurBar-side_margin, 9-hauteurBar);
    glEnd();
    glFlush();
}
