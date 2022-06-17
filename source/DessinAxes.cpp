#include <windows.h>
#include <GL/glut.h>
#include "../include/Affichage.h"


//Fonctions D'affichage des Axes
void afficher_axes(){
    //  Axe des abscises
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2d(0 , 0);  glVertex2d(18 , 0);
    glEnd();
    //Axe des ordonnées
    glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2d(0 , 0);  glVertex2d(0 , 18);
    glEnd();

    //fleche axe des abscisses
    glBegin(GL_LINE_STRIP);
        glColor3ub(255, 255, 255);
        glVertex2d(18 , 0.15);
        glVertex2d(18.15 , 0);  glVertex2d(18 , -0.15);
    glEnd();
    // fleche axe des ordonnées
    glBegin(GL_LINE_STRIP);
        glColor3ub(255, 255, 255);
        glVertex2d(0.1 , 18);
        glVertex2d(0 , 18.2);   glVertex2d(-0.1 , 18);
    glEnd();

    //graduations
    //*axe des abscisses
    for(float i=0.3 ; i<18 ; i+=0.3){
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2d(i, 0.1); glVertex2d(i, -0.1);
        glEnd();
        }
    //*axe des ordonnees
    for(float i=0.5333 ; i<18 ; i+=0.55){
        glBegin(GL_LINES);
        glColor3ub(255, 255, 255);
        glVertex2d(0.1, i); glVertex2d(-0.1, i);
        glEnd();
        }

    //Affichage des numeros sur l'axe des abscisses
    char numero_abs[5];
    double j=-0.06;
    for(int i=0; i<60 ; i+=2){
        PrintTexte(j, -0.4, 0, itoa(i, numero_abs, 10), GLUT_BITMAP_HELVETICA_12);
        j+=0.6;
    }
    //Affichage des numeros sur l'axe des ordonnees
    char numero_ord[5];
    double pas=0.433;
    for(int i=1; i<33 ; i+=2){
        PrintTexte(-0.4, pas, 0, itoa(i, numero_ord, 10), GLUT_BITMAP_9_BY_15);
        pas+=(0.55*2);
    }

    //Affichage de l'echelle des axes
    glColor3ub(255, 255, 255);
    PrintTexte(18, -0.5, 0, "  x100", GLUT_BITMAP_HELVETICA_12);
    PrintTexte(-0.7, 18, 0, "  x100", GLUT_BITMAP_HELVETICA_12);

    glFlush();
}
