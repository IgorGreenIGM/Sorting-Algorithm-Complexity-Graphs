/**
 *  \brief Programme permettant de calculer le temps d'execution des differents tris algorithmiques( TRI BULLES, TRIS SELECTION, TRI ISERTION)
 * stocke la taille du tableau et le temps correspondant dans des fichiers textes correspondants, avec possibilité de les lire et de tracer
 * les Courbes Correspondantes.............................................................................................................
 * @author MOGOU IGOR GREEN
 * @email igormogou86@gmail.com
 * @language C
 * @Libraries GLUT, OPENGL
 */

#include <windows.h>
#include <GL/glut.h>
#include "../include/Affichage.h"
#include "../include/Menu.h"
#include "../include/Lecture.h"

int main(int argc, char *argv[])
{
    //Fonctions d'initialisation des parametres de la fenetre
    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    //Creation de La fenêtre
    glutCreateWindow("Graphes Complexité");

    //Passage en mode plein ecran
    glutFullScreen();

    //Fonctions de Definition du repere Consulter le repere par defaut d'opengl
    glScalef(0.1, 0.1, 0.1);            //homothétie de rapport 10
    glTranslatef(-9, -9, 0);            //Translation de vecteur(-9, -9, 0)

    //Appel de la fonction De Callback d'Affchage
    glutDisplayFunc(Affichage);

    //Appel de Fonction de Creation du Menu
    ConstruireMenu();
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    return 0;
}
