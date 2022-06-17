
/** \brief Fonction de dessin des courbes, qui consiste en le calcul de l'echelle, l'animation des courbes, le dessin sans animation
 *  des courbes et la generation des couleurs aleatoires
 * \param le drawer designe la fonction de dessin de la courbe, drawer animated effectue une animation de dessin
 * \return Rien.
 */

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <GL/glut.h>
#include "../include/Lecture.h"
#include "../include/Drawer.h"
#include "../include/Structures.h"
#include "../include/Affichage.h"

//Fonction de generation de couleur de maniere Aléatoire
Couleur *CreerCouleurAleatoire()
{
    Couleur *couleur = (Couleur*)malloc(sizeof(*couleur));
    couleur->Rouge = rand()%255;
    couleur->Bleu = rand()%couleur->Rouge +255;
    couleur->Vert = rand()%couleur->Bleu +255;
    return couleur;
}

//Fonction de calcul de la position du drawer.
//Soient A(xa, ya) et B(xb, yb)
//Cette fonction donne la position du drawer a l'interieur du segment [AB]
void CalculPositionDrawer(float xa, float xb, float ya, float yb, Point *drawer)
{
    drawer->y = (float)(((yb - ya)*(drawer->x - xa)))/(xb - xa) + ya;
}

///Fonction de dessin du drawer Pour l'animation qui consiste en le dessin suucessif de points Appartenant au segment [AB]
/// A et B etant definis comme les extermit�s des segments, ces derniers sont lus dans les fichiers correspondants
///Pour changer la vitesse de dessin, il suffit de changer le pas de l'abscisse du Drawer
void DessinerDrawerAnimated(Point *drawer, Point *pointA, Point *pointB, Couleur *couleur)
{
    for(drawer->x = pointA->x ; drawer->x < pointB->x ; drawer->x+=0.000001){
    CalculPositionDrawer(pointA->x, pointB->x, pointA->y, pointB->y, drawer);
    glBegin(GL_POINTS);
    glColor3ub(couleur->Rouge, couleur->Vert, couleur->Bleu);
    glVertex2d(drawer->x, drawer->y);
    glEnd();
    }
    glFlush();
}

//Fonction de dessin d'animation des courbes des tris proprement dits:
void DessinTrisAnimated(int Choix)
{
    Couleur *couleur = (Couleur*)malloc(sizeof(*couleur));      //On cree la couleur
    FILE *fichier = NULL;
    int nombreElements = 0;                                     //On defini le nombre d'elements contenus das le fchier à 0

    switch(Choix){

        case TRI_BULLES:;
            couleur = CreerCouleurAleatoire();                  //On genere la couleur
            fichier = fopen("TriBulles.txt", "r");              //on ouvre le ficher
            nombreElements = CalculNombreLignes(fichier);       //on calcul le nombre d'elements contenus dans le fichier
            DessinBoxTexteTris(TRI_BULLES, couleur);            //On dessin la box du tri dans la legende
        break;

        case TRI_SELECTION:;
            couleur = CreerCouleurAleatoire();
            fichier = fopen("TriSelection.txt", "r");
            nombreElements = CalculNombreLignes(fichier);
            DessinBoxTexteTris(TRI_SELECTION, couleur);
        break;

        case TRI_INSERTION:;
            couleur = CreerCouleurAleatoire();
            fichier = fopen("TriInsertion.txt", "r");
            nombreElements = CalculNombreLignes(fichier);
            DessinBoxTexteTris(TRI_INSERTION, couleur);
        break;

        case COMPARAISON:;
            DessinTrisAnimated(TRI_BULLES);
            DessinTrisAnimated(TRI_SELECTION);
            DessinTrisAnimated(TRI_INSERTION);
        break;
    }
    double *tableauTailles = (double*)malloc(nombreElements*sizeof(double));   //On cree un tableau devant contenir les tailles(abscisses)
    double *tableauTemps = (double*)malloc(nombreElements*sizeof(double));     //On cree un tableau devant contenir les temps(ordonnees)
    int i = 0;

    Point *drawer = (Point*)malloc(sizeof(*drawer));                        //On cree le drawer
    Point *pointA = (Point*)malloc(sizeof(*pointA));                        //On cree le Point A et le point B
    Point *pointB = (Point*)malloc(sizeof(*pointB));

    LectureCoordonnees(fichier, tableauTailles, tableauTemps);          //On lit les tailles et les temps d'execution dans le fichier
                                                                        //Deja multipli�s par l'echelle *Consulter le fichier Lecture.cpp

    while(i< nombreElements-1){
    pointA->x = tableauTailles[i];  pointA->y = tableauTemps[i];    i++;    //On assigne les valeurs des points A et B
    pointB->x = tableauTailles[i];  pointB->y = tableauTemps[i];

    DessinerDrawerAnimated(drawer, pointA, pointB, couleur);                //On dessine le segment A et B par animation
    }
    free(drawer);     free(pointA);   free(pointB);   free(couleur);
    fclose(fichier);
    glFlush();
}

//Meme principe que la fonction d'animation, mais dans ce cas on dessinera directement le segment [AB]
void DessinTris(int Choix)
{
    Couleur *couleur = (Couleur*)malloc(sizeof(*couleur));
    FILE *fichier = NULL;
    int nombreElements = 0;

    switch(Choix)
    {
        case TRI_BULLES:;
            couleur = CreerCouleurAleatoire();
            fichier = fopen("TriBulles.txt", "r");
            nombreElements = CalculNombreLignes(fichier);
            DessinBoxTexteTris(TRI_BULLES, couleur);
        break;

        case TRI_SELECTION:;
            couleur = CreerCouleurAleatoire();
            fichier = fopen("TriSelection.txt", "r");
            nombreElements = CalculNombreLignes(fichier);
            DessinBoxTexteTris(TRI_SELECTION, couleur);
        break;

        case TRI_INSERTION:;
            couleur = CreerCouleurAleatoire();
            fichier = fopen("TriInsertion.txt", "r");
            nombreElements = CalculNombreLignes(fichier);
            DessinBoxTexteTris(TRI_INSERTION, couleur);
        break;

        case COMPARAISON:;
            DessinTris(TRI_BULLES);
            DessinTris(TRI_SELECTION);
            DessinTris(TRI_INSERTION);
        break;
    }
    double *tableauTailles = (double*)malloc(nombreElements*sizeof(double));
    double *tableauTemps = (double*)malloc(nombreElements*sizeof(double));
    int i = 0;

    Point *pointA = (Point*)malloc(sizeof(*pointA));
    Point *pointB = (Point*)malloc(sizeof(*pointB));

    LectureCoordonnees(fichier, tableauTailles, tableauTemps);

    while(i< nombreElements-1){
    pointA->x = tableauTailles[i];  pointA->y = tableauTemps[i];    i++;    //Incrementation A et B| A->B et B->suivant(B)
    pointB->x = tableauTailles[i];  pointB->y = tableauTemps[i];

    glBegin(GL_LINES);                                                  //Dessin du segment [AB]
    glVertex2d(pointA->x, pointA->y);
    glVertex2d(pointB->x, pointB->y);
    glEnd();
    }
    free(pointA);   free(pointB);   free(couleur);
    fclose(fichier);
    glFlush();
}
