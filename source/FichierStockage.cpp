/** \brief Fonction de stockage de donn�es(taiile et temps d'execution) des differents tris dans des fichiers textes
 *  La fonction FileStorage permet l'enregistrement proprement dite, et la fonction Appel permet le choix du tri pour le calcul, ainsi aue la barre de chargement
 *  qui indique l'etat d'avancement du calcul en fonction de la limite definie ---Consulter le fichier LoadingBar
 * \param la taille maximale du tableau et le pas(on effectuera d'abord le tri sur un tableau de 1*pas, ensuite 2*pas, 3*pas ainsi de suite) jusqu'a atteindre la limite)
 * \param le choix qui permet de selectionner l'algorithme de tri dont on veut effectuer le calcul
 * \return Rien. mais un fichier est crée contenant les resulats
 */

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "../include/TrisFunctions.h"
#include "../include/LoadingBar.h"
#include "../include/Structures.h"

//Fonction de stockage, Consulter la fonction Calcul temps
void FileStorage(FILE *fichier, int *tableau, int taille, int choix)
{
    switch(choix)
    {
        case TRI_BULLES:
            fprintf(fichier, "%d %1.2f\n", taille, Calcultemps(tableau, choix, taille));
        break;

        case TRI_SELECTION:
            fprintf(fichier, "%d %1.2f\n", taille, Calcultemps(tableau, choix, taille));
        break;

        case TRI_INSERTION :
            fprintf(fichier, "%d %1.2f\n", taille, Calcultemps(tableau, choix, taille));
        break;
    }
}

//Fonction d'Appel
void AppelFonctionStockage(int Choix, char *chemin, int SIZE_MAX, int pas)
{
    FILE *fichier = fopen(chemin, "w+");    //On crée le fichier

    //On cree un tableau de taille maximale et on le remplie avec des valeurs aléatoires
    int *tableau = (int*)malloc(SIZE_MAX*sizeof(int));
    remplir_tableau(tableau, SIZE_MAX, 500);
    int taille = 0;                        //On initialise la taille du tableau actuel à 0(taille qu'on stockera dans le fichier)

    int nbrePas = 1, etat =0;               //On definit le nombre de pas effectués et l'etat d'avancement
    long double echelle = (long double)((long double)4/(long double)SIZE_MAX);      //On definit l'echelle pour la generation de la barre

    DrawProgressBarBackground(4, 0.7, 0.04, 0.05); //On dessine prealablement le background pour la ProgressBar(Rectangle Blanc)
    for(int i=0; i <= SIZE_MAX ; i+=pas)
    {
        int *tableauCopie = (int*)malloc(i*sizeof(int));    //On copie les valeurs du tableau Max dans un nouveau tableau de taille Pas
        copier_tableau(tableauCopie, tableau, pas);
        FileStorage(fichier, tableauCopie, taille, Choix);  //On stocke les donnees
        free(tableauCopie);
        taille+=pas;

        etat = nbrePas*pas;                                 //On change l'etat d'avancement
        DrawProgressBarBackground(4, 0.7, 0.04, 0.05);      //On redessine le background de la ProgressBar
        DrawProgressBar(etat, SIZE_MAX, echelle, 4, 0.7, 0.04, 0.05);       //On dessine et met a jour la barre de progression
        nbrePas++;                                                          //On incremente le nombre de pas effectués
    }
    Sleep(500);                                                             //On endort le programme de 0.5 sec
    CLearProgressBar(4,0.7, 0.04, 0.05);                                    //On efface la barre de progression une fois le calcul et le stockage terminés
    fclose(fichier);
}
