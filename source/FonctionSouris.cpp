
/** \brief Fonction de gestion de la souris Si un click est effectu� dans la zone d'un point, un rectangle d'information s'affiche
    avec les coordonnées correspondantes à celles stockées dans les fichiers.

    \IMPORTANT Le syteme de coordonnées de la souris a son origine a l'extreme haut gauche, de largeur glutGet(GLUT_SCREEN_WIDTH2)
                Et de hauteur glutGet(GLUT_SCREEN_HEIGHT), il est necessaire de changer ces valeurs pour coincider dans notre
                propre systeme de coordonnées à travers la fonction *CalculCoordChangementRepere*

 * \return Rien.
 */

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../include/TrisFunctions.h"
#include "../include/Structures.h"
#include "../include/Constantes.h"
#include "../include/Affichage.h"
#include "../include/Lecture.h"
#include "../include/Souris.h"

int nbClicksEffectues = 0, k=0;                                         //On initialise le nombre de clicks effectués
int *AbscissesClicks = (int*)malloc(NB_CLICKS_MAX*sizeof(int));         //Tableaux devant contenir les coordonnées des clicks precedents,
int *OrdonneesClicks = (int*)malloc(NB_CLICKS_MAX*sizeof(int));         //Utile pour effacer le rectangle d'information

// Fonctions de test si le click est realis�, on testera ulterieurement si
// le curseur est dans une zone de Point

void OnClickOverTriBulles(int boutton, int state, int x, int y)             //Pour le tri Bulles, x, y sont les coordonnées de la souris
{
    afficher_axes();                                                        //A chaque click, on affichera prealablement les axes

    if(boutton == GLUT_LEFT_BUTTON && state == GLUT_DOWN)                   //on verifie si le click est effectué
    {
        AbscissesClicks[nbClicksEffectues] = x;                             //On stocke la position
        OrdonneesClicks[nbClicksEffectues] = y;

        CreationZoneSouris(x, y, RAYON, TRI_BULLES);                        //On dessine si le curseur est dans la zone souris du au tri Bulles
        nbClicksEffectues++;                                                //On incremente le nombre de tri

        k=nbClicksEffectues-2;                                              //Pour des questions d'otimisation, on n'effacerra que
                                                                            //Le rectangle precedement dessiné, d'ou la variable *k*
        for(int i = k; i<nbClicksEffectues-1; i++)
        {
            EraseRectCoordInfo(AbscissesClicks[i]+BOX_MARGIN, OrdonneesClicks[i]+BOX_MARGIN);       //On efface le rectangle precedent
        }
        CreationZoneSouris(x, y, RAYON, TRI_BULLES);                        //On redessine En cas de supperposition du rectangle d'affichage et d'effacement
        k++;                                                                //On change le rectangle precedent
    }
}

void OnClickOverTriSelection(int boutton, int state, int x, int y)          //meme procédé, mais pour la courbe du tri Selection
{
    afficher_axes();
    if(boutton == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        AbscissesClicks[nbClicksEffectues] = x;
        OrdonneesClicks[nbClicksEffectues] = y;

        CreationZoneSouris(x, y, RAYON, TRI_BULLES);
        nbClicksEffectues++;

        k=nbClicksEffectues-2;

        for(int i = k; i<nbClicksEffectues; i++)
        {
            EraseRectCoordInfo(AbscissesClicks[i]+BOX_MARGIN, OrdonneesClicks[i]+BOX_MARGIN);
        }
        CreationZoneSouris(x, y, RAYON, TRI_SELECTION);
        k++;
    }
}

void OnClickOverTriInsertion(int boutton, int state, int x, int y)          //meme proc�d�, mais pour la courbe du tri Insertion
{
    afficher_axes();
    if(boutton == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        AbscissesClicks[nbClicksEffectues] = x;
        OrdonneesClicks[nbClicksEffectues] = y;

        CreationZoneSouris(x, y, RAYON, TRI_BULLES);
        nbClicksEffectues++;

        k=nbClicksEffectues-2;

        for(int i = k; i<nbClicksEffectues; i++)
        {
            EraseRectCoordInfo(AbscissesClicks[i]+BOX_MARGIN, OrdonneesClicks[i]+BOX_MARGIN);
        }
        CreationZoneSouris(x, y, RAYON, TRI_INSERTION);
        k++;
    }
}

void CalculCoordChangementRepere(GLdouble *x, GLdouble *y)   //Fonction de changement des ccordonnées du repere de la souris dans notre repere Opengl
{
    int largeurEcran = glutGet(GLUT_SCREEN_WIDTH), hauteurEcran = glutGet(GLUT_SCREEN_HEIGHT);
    *x = 20*(*x)/(largeurEcran) -1;
    *y = 18 - (20*(*y)/(hauteurEcran) -1);
}

void DessinRectCoordInfo(int x, int y)
{
    GLdouble cursor_x = (GLdouble)x;
    GLdouble cursor_y = (GLdouble)y;
    CalculCoordChangementRepere(&cursor_x, &cursor_y);

    glPoint *hG=(glPoint*)malloc(sizeof(*hG));  glPoint *hD=(glPoint*)malloc(sizeof(*hD));
    glPoint *bG=(glPoint*)malloc(sizeof(*bG));  glPoint *bD=(glPoint*)malloc(sizeof(*bG));

    hG->x = cursor_x; hG->y = cursor_y;                                           hD->x = cursor_x+LARGEUR_RECT_INFO; hD->y = cursor_y;
    bG->x = cursor_x+LARGEUR_RECT_INFO; bG->y = cursor_y+HAUTEUR_RECT_INFO;       bD->x = cursor_x; bD->y = cursor_y+HAUTEUR_RECT_INFO;

    glBegin(GL_QUADS);
    glColor3ub(255, 255, 255);
    glVertex2d(hG->x, hG->y);   glVertex2d(hD->x, hD->y);
    glVertex2d(bG->x, bG->y);   glVertex2d(bD->x, bD->y);
    glEnd();
    free(hG);  free(hD);    free(bG);   free(bD);
    glFlush();
}

//Fonction permettant d'effacer un rectangle(dessin d'un rectangle Noir au coordonnées définies)
void EraseRectCoordInfo(int x, int y)
{
    GLdouble cursor_x = (GLdouble)x;
    GLdouble cursor_y = (GLdouble)y;
    CalculCoordChangementRepere(&cursor_x, &cursor_y);          //on change les coordonnées du curseur pour coincider avec le notre

    /// h=Haut, G=gauche, b=Bas, D=Droite
    glPoint *hG=(glPoint*)malloc(sizeof(*hG));  glPoint *hD=(glPoint*)malloc(sizeof(*hD));
    glPoint *bG=(glPoint*)malloc(sizeof(*bG));  glPoint *bD=(glPoint*)malloc(sizeof(*bG));

    hG->x = cursor_x; hG->y = cursor_y;                                             hD->x = cursor_x+LARGEUR_RECT_INFO; hD->y = cursor_y;
    bG->x = cursor_x+LARGEUR_RECT_INFO; bG->y = cursor_y+HAUTEUR_RECT_INFO;         bD->x = cursor_x; bD->y = cursor_y+HAUTEUR_RECT_INFO;

    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2d(hG->x, hG->y);   glVertex2d(hD->x, hD->y);
    glVertex2d(bG->x, bG->y);   glVertex2d(bD->x, bD->y);
    glEnd();
    free(hG);  free(hD);    free(bG);   free(bD);
    glFlush();
}

//Pour verifier si le curseur de trouve dans une Zone de point, on calcule la distance entre le curseur et le point
GLdouble CalculDistancePointCurseur(int cur_x, int cur_y, GLdouble point_x, GLdouble point_y)
{
    GLdouble cursor_x = (GLdouble)cur_x;
    GLdouble cursor_y = (GLdouble)cur_y;

    CalculCoordChangementRepere(&cursor_x, &cursor_y);
    GLdouble distance = sqrt( pow(cursor_x - point_x, 2.0) + pow(cursor_y - point_y, 2.0));
    return distance;
}

//Fonction de dessin du texte(etat d'avancement) dans la barre de chargement
void DessinCoordPoint(int xForDraw, int yForDraw, float xForScreen, float yForScreen)
{
    char Taille[10];
    char Temps[10];
    glColor3ub(0, 0, 0);

    GLdouble double_x = (GLdouble)xForDraw;
    GLdouble double_y = (GLdouble)yForDraw;

    CalculCoordChangementRepere(&double_x, &double_y);

    PrintTexte(double_x, double_y, 0, itoa(xForScreen, Taille, 10), GLUT_BITMAP_9_BY_15);
    PrintTexte(double_x+TEXT_IN_BOX_SPACING_ABS_ORD, double_y, 0, itoa(yForScreen, Temps, 10), GLUT_BITMAP_9_BY_15);
}

//Fonction permettant de gerer les clicks souris dans les zones de point
void CreationZoneSouris(int cur_x, int cur_y, GLdouble rayon, int choix)
{
    FILE *fichier = NULL;                           //On cree un fichier
    int textScale_x, textScale_y;                   //On definit le scale du texte � Afficher dans les rectangles d'informations

    switch(choix)                                   //En fonction du choix du tri, on ouvre un fichier
    {
        case TRI_BULLES:
            fichier = fopen("TriBulles.txt", "r");
            RechercheDernierPoint("TriBulles.txt", &textScale_x, &textScale_y);
        break;

        case TRI_SELECTION:
            fichier = fopen("TriSelection.txt", "r");
            RechercheDernierPoint("TriSelection.txt", &textScale_x, &textScale_y);
        break;

        case TRI_INSERTION:
            fichier = fopen("TriInsertion.txt", "r");
            RechercheDernierPoint("TriInsertion.txt", &textScale_x, &textScale_y);
        break;
    }

    //On parametre le scale du texte pour que les coordonn�es a aficher ne depassent pas 999(03 chiffres)
    float textScaleFloat_x = (float)textScale_x/999;
    float textScaleFloat_y = (float)textScale_y/999;

    int nombreElements = CalculNombreLignes(fichier);                               //On calcule le nombre de Point scontenus dans le fichier

    //On cree des tableaux devant contenir les coordonn�es des points Dessinés(deja multipliées par l'echelle)
    GLdouble *tableauAbscisses = (GLdouble*)malloc(nombreElements*sizeof(GLdouble));
    GLdouble *tableauOrdonnees = (GLdouble*)malloc(nombreElements*sizeof(GLdouble));

    GLdouble *distance = (GLdouble*)malloc(nombreElements*sizeof(GLdouble));  //Tableau devant contenir les distances du curseur au differents points

    //Tableaux devant contenir les points à Afficher
    float *tableauTailles = (float*)malloc(nombreElements*sizeof(float));
    float *tableauTemps = (float*)malloc(nombreElements*sizeof(float));

    Lecture(fichier, tableauTailles, tableauTemps);                         ///On stocke les Coordonnées à Afficher
    LectureCoordonnees(fichier, tableauAbscisses, tableauOrdonnees);        ///On stocke les Coordonnées des differents points sur le graphe

    ///Pour la position actuelle du curseur, on calcule les distances de chacun des points au curseur
    for(int i=0; i<nombreElements-1; i++)
    {
        distance[i] = CalculDistancePointCurseur(cur_x, cur_y, tableauAbscisses[i], tableauOrdonnees[i]);
    }

    /** On recherche dans le tableau des distances la premiere pour laquelle cette distance est inferieure au rayon
        si elle est trouvée, on dessine le rectangle d'information et les coordonnées à Aficher,on sort de la boucle-lire Constantes.h pour les defines
    */
    for(int i=0; i<nombreElements-1; i++)
    {
        if(distance[i] <= rayon)
        {
            DessinRectCoordInfo(cur_x+BOX_MARGIN, cur_y+BOX_MARGIN);
            DessinCoordPoint(cur_x+BOX_MARGIN+TEXT_IN_BOX_MARGIN_X,
                             cur_y+BOX_MARGIN+TEXT_IN_BOX_MARGIN_Y,
                             (double)tableauTailles[i]/textScaleFloat_x,
                             (double)tableauTemps[i]/(double)textScaleFloat_y);
            break;
        }
    }
    free(tableauAbscisses);     free(tableauOrdonnees);     free(tableauTailles);   free(tableauTemps);     free(distance);
    fclose(fichier);
}
