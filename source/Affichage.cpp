#include <windows.h>
#include <GL/glut.h>
#include <time.h>

#include "../include/Affichage.h"
#include "../include/Structures.h"
#include "../include/Drawer.h"

/** Fonction d'Affichage principale contenant toutes les fonctions de dessin necessaires*/

void Affichage()
{
    //Initialisation des options graphiques
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glEnable(GL_DOUBLEBUFFER);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(1.0f);

    srand(time(NULL));

    //Fonctions de Dessins
    afficher_axes();
    DessinTexteTris(COMPARAISON);
    DessinTrisAnimated(COMPARAISON);

    glDisable(GL_BLEND);
    glDisable(GL_DOUBLEBUFFER);
    glFlush();
}
