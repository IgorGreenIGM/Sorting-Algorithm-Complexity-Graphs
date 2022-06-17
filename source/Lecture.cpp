#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "../include/Constantes.h"
#include "../include/Structures.h"
#include "../include/TrisFunctions.h"

//double echelle_x, echelle_y;

//Fonction de calcul du nombre de lignes contenus dans le fichier --En l'occurence les nombre des points(taille et temps d'execution)
int CalculNombreLignes(FILE *fichier)
{
    char fin[100] = "";
    int nombre = 0;
    while(fgets(fin, 100, fichier) != NULL){
        nombre++;
    }
    rewind(fichier);
    return nombre;
}

//Fonction permettant de se placer a la derniere ligne du fichier
void Rewind_toLastLineBegining(FILE *fichier)
{
    fseek(fichier, 0, SEEK_END);
    fseek(fichier, -1, SEEK_CUR);
    while(fgetc(fichier) != '\n'){
        fseek(fichier, -2, SEEK_CUR);
    }
}

//Fonction de recherche du dernier point dans un fichier(correspondznt a la derniere ligne)
void RechercheDernierPoint(char *chemin, int *x, int *y)
{
    FILE *fichier = fopen(chemin, "r");
    Rewind_toLastLineBegining(fichier);
    fscanf(fichier, "%d %d", x, y);
    fclose(fichier);
}

//Fonction de lecture des points dans un fichier et stockage de ces points dans les tableaux correspondants
void Lecture(FILE *fichier, float *tableauTailles, float *tableauTemps){

    rewind(fichier);
    char fin[100]="";
    int i=0;
    int taille = 0, temps = 0;

    while(fgets(fin, 100, fichier)!=NULL)
    {
        sscanf(fin, "%d %d", &taille, &temps);
        tableauTailles[i] = (float)(taille);
        tableauTemps[i] = (float)(temps);
        i++;
    }
    rewind(fichier);
}

///Fonction de calcul de l'echelle
/**Elle consiste en la recherche des maximums des differents fichier(tri bulles, tri selection et tri insertion)
et en fonction de ce maximum un echelle est calcul�e pour que l'affichage de la courbe ne depasse pas l'ecran,
c'est à dire doit tenir sur total de **18**pixels       -*-*Consulter le main pour la matrice de changement de repere initiale*/
void CalculEchelle(double *echelle_x, double *echelle_y)
{
    char chemin1[]="TriBulles.txt";                     //On defini les chemins d'acces des differents fichers
    char chemin2[]="TriSelection.txt";
    char chemin3[]="TriInsertion.txt";

    int dernieresTailles[3];                            //On defini les tableaux devant contenir les abscisses et les ordonnées maximales
    int derniersTemps[3];

    //On stocke les derniers points dans le tableau
    RechercheDernierPoint(chemin1, &(dernieresTailles[0]), &(derniersTemps[0]));
    RechercheDernierPoint(chemin2, &(dernieresTailles[1]), &(derniersTemps[1]));
    RechercheDernierPoint(chemin3, &(dernieresTailles[2]), &(derniersTemps[2]));

    triInsertion(dernieresTailles, 3);              //On tris les tableaux pour placer le maximum et le minimum en fin de tableau
    triInsertion(derniersTemps, 3);

    //On calcule l'echelle
    *echelle_x = (double)LARGEUR_COURBE_LIMITE/dernieresTailles[2];
    *echelle_y = (double)HAUTEUR_COURBE_LIMITE/derniersTemps[2];
}


//Fonction permettant de lire les points dans un fichier, directement multipli�s par l'echelle
//et stock�s dans les tableax correspondants
void LectureCoordonnees(FILE *fichier, GLdouble *tableauTailles, GLdouble *tableauTemps)
{
    double echelleX, echelleY;              //On definit et calcule l'echelle
    CalculEchelle(&echelleX, &echelleY);

    rewind(fichier);
    char fin[100]="";
    int i=0;
    int taille = 0, temps = 0;

    while(fgets(fin, 100, fichier)!=NULL)
    {
        sscanf(fin, "%d %d", &taille, &temps);
        tableauTailles[i] = (GLdouble)(taille);
        tableauTemps[i] = (GLdouble)(temps);

        tableauTailles[i] = (GLdouble)echelleX*tableauTailles[i];
        tableauTemps[i] = (GLdouble)echelleY*tableauTemps[i];
        i++;
    }
    rewind(fichier);
}
