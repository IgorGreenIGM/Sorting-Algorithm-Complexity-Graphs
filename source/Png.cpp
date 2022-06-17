/** \brief This File Should take a screenshot and store it into a .PNG file
 *         *********************************************************Feature
 * \param
 * \param
 * \return
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include "../include/Structures.h"
#include "../include/FichierStockage.h"


typedef struct CHUNK_IHDR{
    int length;    //4 octets
    unsigned char *type;           //4 octets
    int width;
    int height;
    unsigned char *data;                  //variable
    int *All_Data;
    unsigned long crc;                //4octets
}CHUNK_IHDR;

typedef struct CHUNK_IDAT{
    int length;    //4 octets
    unsigned char *type;           //4 octets
    unsigned char *data;                  //variable
    unsigned long crc;                //4octets
}CHUNK_IDAT;

typedef struct CHUNK_IEND{
    int length;    //4 octets
    unsigned char *type;           //4 octets
    unsigned char *data;                  //variable
    unsigned long crc;                //4octets
}CHUNK_IEND;

typedef struct PNG{
    unsigned char signature[8];
    CHUNK_IHDR IHDR;  //sur 25 octets
    CHUNK_IDAT IDAT; //longueur variable
    CHUNK_IEND IEND; //sur 12 octets
}PNG;


void concat(int *All_DataResult, unsigned char *CHUNK_data, int lenA, int lenB)
{
    int *castingArray = (int*)malloc(lenB*sizeof(int));
    int k=0;

    for(int i=0; i<lenB; i++)
    {
        castingArray[i] = CHUNK_data[i];
    }

    for(int j=lenA; j<lenA+lenB; j++)
    {
        All_DataResult[j] = castingArray[k];
        k++;
    }
}

///Initialisation des datas des CHUNKS-------------------------------------------------------------------------------------------------///
void InitialiserDatas_CHUNK_IHDR(CHUNK_IHDR *IHDR, int largeur, int hauteur)
{
    IHDR->width = largeur;
    IHDR->height = hauteur;

    IHDR->data = (unsigned char*)malloc(5*sizeof(unsigned char));
    IHDR->data[0] = 16;
    IHDR->data[1] = 2;
    IHDR->data[2] = 0;
    IHDR->data[3] = 0;
    IHDR->data[4] = 0;

    IHDR->All_Data = (int*)malloc(11*sizeof(int));
    IHDR->All_Data[0] = IHDR->type[0];
    IHDR->All_Data[1] = IHDR->type[1];
    IHDR->All_Data[2] = IHDR->type[2];
    IHDR->All_Data[3] = IHDR->type[3];
    IHDR->All_Data[4] = IHDR->width;
    IHDR->All_Data[5] = IHDR->height;

    concat(IHDR->All_Data, IHDR->data, 6, 5);
}

void InitialiserDatas_CHUNK_IDAT(CHUNK_IDAT *IDAT, unsigned char *pixels, int nbrePixels)
{
    IDAT->data = (unsigned char*)malloc(nbrePixels*sizeof(unsigned char));
    for(int i=0; i<nbrePixels; i++){
        IDAT->data[i] = pixels[i];
    }
}


void InitialiserDatas_CHUNK_IEND(CHUNK_IEND *IEND)
{
    IEND->data = NULL;
}

///Initialisation des CHUNK------------------------------------------------------------------------------------------------------------///
void Initialiser_CHUNK_IHDR(CHUNK_IHDR *IHDR, int largeur, int hauteur)
{
    IHDR->length = 5;

    IHDR->type = (unsigned char*)malloc(4*sizeof(unsigned char));
    IHDR->type[0] = 73;
    IHDR->type[1] = 72;
    IHDR->type[2] = 68;
    IHDR->type[3] = 82;

    InitialiserDatas_CHUNK_IHDR(IHDR, largeur, hauteur);
    IHDR->crc = crc(IHDR->data, 11);
}

void Initialiser_CHUNK_IDAT(CHUNK_IDAT *IDAT, unsigned char *pixels, int nbrePixels)
{
    IDAT->length = nbrePixels;

    IDAT->type = (unsigned char*)malloc(4*sizeof(unsigned char));
    IDAT->type[0] = 73;
    IDAT->type[1] = 68;
    IDAT->type[2] = 65;
    IDAT->type[3] = 84;

    InitialiserDatas_CHUNK_IDAT(IDAT, pixels, nbrePixels);
    IDAT->crc = crc(IDAT->data, IDAT->length);
}

void Initialiser_CHUNK_IEND(CHUNK_IEND *IEND)
{
    IEND->length = 0;

    IEND->type = (unsigned char*)malloc(4*sizeof(unsigned char));
    IEND->type[0] = 73;
    IEND->type[1] = 69;
    IEND->type[2] = 78;
    IEND->type[3] = 68;

    InitialiserDatas_CHUNK_IEND(IEND);
    IEND->crc = crc(IEND->type, 4);
}


///Enregistrement des chunks-------------------------------------------------------------------------------------------------------------
void SaveIHDR(FILE *fp, CHUNK_IHDR *IHDR, int largeur, int hauteur)
{
    Initialiser_CHUNK_IHDR(IHDR, largeur, hauteur);
    fwrite((void*)&(IHDR->length), sizeof(int), 1, fp);                             //Pour LA lenght
    fwrite((void*)(IHDR->type), 4*sizeof(unsigned char), 4, fp);      //Pour LE type du CHUNK*/
    fwrite((void*)&(IHDR->width), sizeof(int), 1, fp);
    fwrite((void*)&(IHDR->height), sizeof(int), 1, fp);
    fwrite((void*)(IHDR->data), 7*sizeof(unsigned char), 7, fp);  //Pour LES DATAS DU CHUNK
    fwrite((void*)&(IHDR->crc), 1*sizeof(int), 1, fp);                              //Pour LE crc du CHUNK*//*
}

void SaveIDAT(FILE *fp, CHUNK_IDAT *IDAT,unsigned char *pixels, int nbrePixels)
{
    Initialiser_CHUNK_IDAT(IDAT, pixels, nbrePixels);
    fwrite((void*)&(IDAT->length), sizeof(int), 1, fp);                             //Pour LA lenght
    fwrite((void*)(IDAT->type), 4*sizeof(unsigned char), 4, fp);      //Pour LE type du CHUNK
    //fwrite((void*)(IDAT->data), nbrePixels*sizeof(unsigned char), nbrePixels, fp);  //Pour LES DATAS DU CHUNK
    fwrite((void*)&(IDAT->crc), 1*sizeof(int), 1, fp);                              //Pour LE crc du CHUNK*//*
}

void SaveIEND(FILE *fp, CHUNK_IEND *IEND)
{
    Initialiser_CHUNK_IEND(IEND);
    fwrite((void*)&(IEND->length), sizeof(int), 1, fp);                             //Pour LA lenght
    fwrite((void*)(IEND->type), 4*sizeof(unsigned char), 4, fp);      //Pour LE type du CHUNK*/
    fwrite((void*)&(IEND->crc), 1*sizeof(int), 1, fp);                              //Pour LE crc du CHUNK*//*/*
}


void Png(int largeur, int hauteur, int canaux)
{
    int nbrePixels = largeur*hauteur*canaux;
    unsigned char *pixels = (unsigned char*)malloc(nbrePixels*sizeof(unsigned char));

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0.0, 0.0, (short)largeur, (short)hauteur, GL_RGB, GL_UNSIGNED_BYTE, pixels); //*/

    PNG *myPNG = (PNG*)malloc(sizeof(*myPNG));
    myPNG->signature;

    /*myPNG->signature[0] = 0x89;
    myPNG->signature[1] = 0x50;
    myPNG->signature[2] = 0x4E;
    myPNG->signature[3] = 0x47;
    myPNG->signature[4] = 0x0D;
    myPNG->signature[5] = 0x0A;
    myPNG->signature[6] = 0x1A;
    myPNG->signature[7] = 0x0A;*/

    FILE *fp = fopen("Graphe.png", "wb+");

    fwrite(myPNG->signature, 8*sizeof(unsigned char), sizeof(unsigned char), fp);   //Pour LA signature

    fclose(fp);

    /*SaveIHDR(fp, myPNG->IHDR, largeur, hauteur);

    SaveIDAT(fp, myPNG->IDAT, pixels, nbrePixels);

    fwrite(pixels, nbrePixels, 1, fp);

    SaveIEND(fp, myPNG->IEND);//*/

    fclose(fp);
    free(myPNG);
}
