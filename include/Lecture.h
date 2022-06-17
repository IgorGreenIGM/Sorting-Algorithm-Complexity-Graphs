#ifndef LECTURE_H_INCLUDED
#define LECTURE_H_INCLUDED

#include "../include/Structures.h"
#include <stdio.h>

void Lecture(FILE *fichier, float *tableauTailles, float *tableauTemps);

void LectureCoordonnees(FILE *fichier, GLdouble *tableauTailles, GLdouble *tableauTemps);

int CalculNombreLignes(FILE *fichier);

void Rewind_toLastLineBegining(FILE *fichier);

void RechercheDernierPoint(char *chemin, int *x, int *y);

void CalculEchelle(double *echelle_x, double *echelle_y);

#endif // LECTURE_H_INCLUDED
