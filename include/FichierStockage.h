#ifndef FICHIERSTOCKAGE_H_INCLUDED
#define FICHIERSTOCKAGE_H_INCLUDED
#include <stdio.h>

void FileStorage(FILE *fichier, int *tableau, int taille, int choix);

void AppelFonctionStockage(int Choix, char *chemin, int SIZE_MAX, int pas);

int crc(unsigned char *dataChunk, int len);

void ScreenToBitmap(char *chemin);

void concat(int *All_DataResult, unsigned char *CHUNK_data, int lenA, int lenB);

#endif // FICHIERSTOCKAGE_H_INCLUDED
