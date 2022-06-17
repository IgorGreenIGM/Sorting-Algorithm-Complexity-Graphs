
/** Fonction de Dessin d'informations, A savoir le Texte D'echelle, l'echelle et les Couleurs correspondantes
*/
#include <windows.h>
#include <GL/glut.h>
#include "../include/Affichage.h"
#include "../include/Structures.h"

//Fonction d'Ecriture du texte du l'ecran
void PrintTexte(float x, float y, float z, char *chaine, void *font)
{
    glRasterPos3d(x, y, z);
    for(int i=0; i<strlen(chaine) ; i++ )
    {
        glutBitmapCharacter(font, chaine[i]);
    }
}

//Dessin des box de couleurs dans la legende corresondantes aux differents tris
void DessinBoxTexteTris(int choix, Couleur *couleur)
{
    switch(choix)
    {

    case TRI_BULLES:
        glBegin(GL_QUADS);
        glColor3ub(couleur->Rouge, couleur->Vert, couleur->Bleu);
        glVertex2d(16.2, 18.2);
        glVertex2d(16.8, 18.2);
        glVertex2d(16.8, 18);
        glVertex2d(16.2, 18);
        glEnd();
        glFlush();
    break;

    case TRI_SELECTION:
        glBegin(GL_QUADS);
        glColor3ub(couleur->Rouge, couleur->Vert, couleur->Bleu);
        glVertex2d(16.2, 17.7);
        glVertex2d(16.8, 17.7);
        glVertex2d(16.8, 17.5);
        glVertex2d(16.2, 17.5);
        glEnd();
        glFlush();
    break;

    case TRI_INSERTION:
        glBegin(GL_QUADS);
        glColor3ub(couleur->Rouge, couleur->Vert, couleur->Bleu);
        glVertex2d(16.2, 17.2);
        glVertex2d(16.8, 17.2);
        glVertex2d(16.8, 17);
        glVertex2d(16.2, 17);
        glEnd();
        glFlush();
    break;
    }
}

//On Affiche le texte des tris correspondants
void DessinTexteTris(int choix)
{
    switch(choix)
    {
        case TRI_BULLES:
            PrintTexte(17, 18, 0, "TRI BULLES", GLUT_BITMAP_HELVETICA_12);
        break;

        case TRI_SELECTION:
            PrintTexte(17, 17.5, 0, "TRI SELECTION", GLUT_BITMAP_HELVETICA_12);
        break;

        case TRI_INSERTION:
            PrintTexte(17, 17, 0, "TRI INSERTION", GLUT_BITMAP_HELVETICA_12);
        break;

        case COMPARAISON:
            PrintTexte(17, 18, 0, "TRI BULLES", GLUT_BITMAP_HELVETICA_12);
            PrintTexte(17, 17.5, 0, "TRI SELECTION", GLUT_BITMAP_HELVETICA_12);
            PrintTexte(17, 17, 0, "TRI INSERTION", GLUT_BITMAP_HELVETICA_12);
        break;
    }
}
