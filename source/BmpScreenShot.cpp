/** \brief Fonction d'enregistrement de l'Ecran actuel dans un fichier au format BMP
 *  Lire la page wikipedia sur la structure d'un fichier BMP pour plus d'informations sur sa structure
 * \param   chemin d'acces vers l'emplacement de sauvegarde
 * \param   la taille de l'ecran(largeur, hauteur en pixels) et le mode des couleurs(RBG, BGR...)
 * \return  Rien.
 */

#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdint.h>

/// Constantes du Fichier BMP
#define _height glutGet(GLUT_SCREEN_HEIGHT)
#define _width glutGet(GLUT_SCREEN_WIDTH)
#define _bitsperpixel 24
#define _planes 1
#define _compression 0
#define _pixelbytesize _height*_width*_bitsperpixel/8
#define _filesize _pixelbytesize+sizeof(bitmap)
#define _xpixelpermeter 0x130B
#define _ypixelpermeter 0x130B

#pragma pack(push,1)
typedef struct
{
    uint8_t signature[2];
    uint32_t filesize;
    uint32_t reserved;
    uint32_t fileoffset_to_pixelarray;
} fileheader;                           //Structure du Header par defaut du BMP

typedef struct
{
    uint32_t dibheadersize;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsperpixel;
    uint32_t compression;
    uint32_t imagesize;
    uint32_t ypixelpermeter;
    uint32_t xpixelpermeter;
    uint32_t numcolorspallette;
    uint32_t mostimpcolor;
} bitmapinfoheader;                 //Structure du Header du fichier en fonction de nos parametres


typedef struct
{
    fileheader fileheader;
    bitmapinfoheader bitmapinfoheader;
} bitmap;                           //Structure de Header

void Inverser_RGB_BGR(unsigned char *pixels, int nbrePixels);    //Fonction d'inversion des couleurs

void ScreenToBitmap(char *chemin)
{
    //la structure des informations du BMP
    FILE *fp = fopen(chemin,"wb");
    bitmap *pbitmap  = (bitmap*)calloc(1,sizeof(bitmap));
    //Le tableau devant contenir les informations des pixels
    uint8_t *pixelbuffer = (uint8_t*)malloc(_pixelbytesize);

    //Remplissage les informations du BMP
    pbitmap->fileheader.signature[0] = 'B';
    pbitmap->fileheader.signature[1] = 'M';
    pbitmap->fileheader.filesize = _filesize;
    pbitmap->fileheader.fileoffset_to_pixelarray = sizeof(bitmap);
    pbitmap->bitmapinfoheader.dibheadersize =sizeof(bitmapinfoheader);
    pbitmap->bitmapinfoheader.width = _width;
    pbitmap->bitmapinfoheader.height = _height;
    pbitmap->bitmapinfoheader.planes = _planes;
    pbitmap->bitmapinfoheader.bitsperpixel = _bitsperpixel;
    pbitmap->bitmapinfoheader.compression = _compression;
    pbitmap->bitmapinfoheader.imagesize = _pixelbytesize;
    pbitmap->bitmapinfoheader.ypixelpermeter = _ypixelpermeter ;
    pbitmap->bitmapinfoheader.xpixelpermeter = _xpixelpermeter ;
    pbitmap->bitmapinfoheader.numcolorspallette = 0;

    //On ecrit le Header dans le fichier
    fwrite (pbitmap, 1, sizeof(bitmap),fp);

    //On ecrit les pixels dans le fichier
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadBuffer(GL_FRONT);
    glReadPixels(0.0, 0.0, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, pixelbuffer);
    Inverser_RGB_BGR(pixelbuffer, _pixelbytesize);
    fwrite(pixelbuffer,1,_pixelbytesize,fp);

    //Fermeture du fichier et liberation de structures
    fclose(fp);
    free(pbitmap);
    free(pixelbuffer);
}

//Le stockage des pixels dans le buffer en RGB, mais l'enregistrement dans un BMP nécessite une inversion des couleurs en BGR
void Inverser_RGB_BGR(unsigned char *pixelbuffer, int nbrePixels)
{
    for(int i=0; i<nbrePixels; i+=3)
    {
        int tmp = pixelbuffer[i];
        pixelbuffer[i] = pixelbuffer[i+2];
        pixelbuffer[i+2] = tmp;
    }
}
