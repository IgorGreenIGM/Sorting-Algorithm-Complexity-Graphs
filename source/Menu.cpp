/** \brief Fonction de Menu pop-up
 */

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/Affichage.h"
#include "../include/Structures.h"
#include "../include/FichierStockage.h"
#include "../include/Drawer.h"
#include "../include/Souris.h"


//Fonction pour le sous-menu Calcul, permettant de caculer les temps et de les stocker
void SubMenuCalcul(int commande)
{
    switch(commande)
    {
        case MENU_TRI_BULLES:{
            AppelFonctionStockage(TRI_BULLES, "FileTriBulles.txt", 16000000, 1000);
            Affichage();
            glFlush();
        }
        break;

        case MENU_TRI_SELECTION:
            AppelFonctionStockage(TRI_SELECTION, "FileTriSelection.txt", 16000000, 1000);
            Affichage();
            glFlush();
        break;

        case MENU_TRI_INSERTION:
            AppelFonctionStockage(TRI_INSERTION, "FileTriInsertion.txt", 16000000, 1000);
            Affichage();
            glFlush();
        break;
    }
}

//Fonction de menu principal
void ChoixMenu(int commande)
{
    switch (commande)
    {
    case MENU_TRI_BULLES:
        glClear(GL_COLOR_BUFFER_BIT);
        afficher_axes();
        DessinTris(TRI_BULLES);
        glColor3ub(255, 255, 255);
        DessinTexteTris(TRI_BULLES);
        glFlush();
        glutMouseFunc(OnClickOverTriBulles);
        glutSwapBuffers();
    break;

    case MENU_TRI_SELECTION:
        glClear(GL_COLOR_BUFFER_BIT);
        afficher_axes();
        DessinTris(TRI_SELECTION);
        glColor3ub(255, 255, 255);
        DessinTexteTris(TRI_SELECTION);
        glFlush();
        glutMouseFunc(OnClickOverTriSelection);
        glutSwapBuffers();
    break;

    case MENU_TRI_INSERTION:
        glClear(GL_COLOR_BUFFER_BIT);
        afficher_axes();
        DessinTris(TRI_INSERTION);
        glColor3ub(255, 255, 255);
        DessinTexteTris(TRI_INSERTION);
        glFlush();
        glutMouseFunc(OnClickOverTriInsertion);
        glutSwapBuffers();
    break;

    case MENU_COMPARAISON:
        glClear(GL_COLOR_BUFFER_BIT);
        afficher_axes();
        DessinTris(COMPARAISON);
        glColor3ub(255, 255, 255);
        DessinTexteTris(COMPARAISON);
        glFlush();
        glutMouseFunc(NULL);
        glutSwapBuffers();
    break;

    case MENU_SCREENSHOT:{
        ScreenToBitmap("Graphe.bmp");}
    break;

    case QUITTER :
        exit(0);
    break;
    }
}

//Fonction de construction du menu
int ConstruireMenu()
{
    int subMenu_Calcul = glutCreateMenu(SubMenuCalcul);
    glutAddMenuEntry("TRI_BULLES", MENU_TRI_BULLES);
    glutAddMenuEntry("TRI SELECTION", MENU_TRI_SELECTION);
    glutAddMenuEntry("TRI_INSERTION", MENU_TRI_INSERTION);

    int menu_id = glutCreateMenu(ChoixMenu);
    glutAddMenuEntry("TRI BULLES", MENU_TRI_BULLES);
    glutAddMenuEntry("TRI SELECTION", MENU_TRI_SELECTION);
    glutAddMenuEntry("TRI INSERTION", MENU_TRI_INSERTION);
    glutAddMenuEntry("COMPARAISON", MENU_COMPARAISON);
    glutAddSubMenu("CALCUL", subMenu_Calcul);
    glutAddMenuEntry("SCREENSHOT", MENU_SCREENSHOT);
    glutAddMenuEntry("QUITTER", QUITTER);
    return menu_id;
}
