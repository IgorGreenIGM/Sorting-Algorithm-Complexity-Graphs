
/** \brief Fonctions des tris et de calcul des temps d'executions
 * \return temps d'execution du tris selectionné
 */

#include <stdlib.h>
#include <time.h>
#include "../include/Structures.h"

//Fonction de remplissage du tableau avec des valeurs al�atoires
void remplir_tableau(int tableau[], int taille, int maximum)
{
    for(int i=0; i<taille ; i++)
    {
        tableau[i] = rand()%maximum;
    }
}

//Fonction du tri Bulles
void tri_Bulles(int *tableau, int fin)
{
    int i=0;
    while(fin != 0)
    {
        for(i=0; i<fin-1; i++)
        {
            if(tableau[i+1] < tableau[i])
            {
                int inter = tableau[i+1];
                tableau[i+1] = tableau[i];
                tableau[i] = inter;
            }
        }
        fin--;
    }
}

//Fonction du tri selection
void triSelection(int *tableau,int taille)
{
    int tmp=0;
    int max=0;
    for(int i=taille-1;i>=0;i--){
        max=i;
        for(int j=i-1;j>=0;j--){
            if(tableau[j]>tableau[max]){
                max=j;
            }
        }
        tmp=tableau[max];
        tableau[max]=tableau[i];
        tableau[i]=tmp;
    }
}

//Fonction du tri Insertion
void triInsertion(int *tableau, int taille)
{
    int x=0, j;
    for(int i=1 ; i<taille ; i++){
       x= tableau[i];
       j = i;

       while(j>0 && tableau[j-1]>x){
        tableau[j] = tableau[j-1];
        j--;
        tableau[j] = x;
       }
    }
}

//Fonction de tri Insertion avec des valeurs decimales doubles
void glDoubleTriInsertion(GLdouble *tableau, int taille)
{
    GLdouble x=0;
    int j=0;
    for(int i=1 ; i<taille ; i++){
       x = tableau[i];
       j = i;

       while(j>0 && tableau[j-1]>x){
        tableau[j] = tableau[j-1];
        j--;
        tableau[j] = x;
       }
    }
}

//Copie du tableau Source(TableauS) dans un tableau destination(TableauD)
void copier_tableau(int *tableauD, int *tableauS, int fin){
    for(int i=0; i<fin; i++){
        tableauD[i] = tableauS[i];
    }
}

//Fonction de calcul du temps d'execution en millisecondes
double Calcultemps(int *tableau, int choix, int fin)
{
    clock_t tps_av = clock();
    clock_t tps_ap = 0;

    switch(choix)
    {
        case TRI_BULLES :
            tri_Bulles(tableau, fin);
            tps_ap = clock();
        break;

        case TRI_SELECTION :
            triSelection(tableau, fin);
            tps_ap = clock();
        break;

        case TRI_INSERTION :
            triInsertion(tableau, fin);
            tps_ap = clock();
        break;
    }
    return (double)(tps_ap-tps_av);
}
