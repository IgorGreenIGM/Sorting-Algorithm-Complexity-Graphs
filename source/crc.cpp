/**
 * \brief Algorithme de calcul de la Somme de controle CRC32 partir des donnees en l'occurence ici pour la generation des crc des fichiers PNG
 * \param Data du CHUNK correspondant
 * \param length des donnees du CHUNK correspondant
 * \return crc du CHUNK correspondant
 */


//table crc contenant et variable de test si la table a deja ete remplie
unsigned long crc_table[255];
int crc_table_computed = 0;

//Creation de la table crc, a noter que cette fonction n'est appell�e qu'une seule fois
void calcul_table_crc()
{
    unsigned long c;
    int i, j;
    for(i=0; i<256; i++){
        c=i;
        for(j=0; j<8; j++){
            if(c & 1){
                c=0xedb88320L ^ (c >> 1);
            }else{
                c = c >> 1;
            }
        }
        crc_table[i]=c;
    }
    crc_table_computed = 1;
}

//Fonction de mise � jour du crc en fonction des datas du CHUNK
unsigned long maj_crc(unsigned long crc, unsigned char *dataCHUNK, int len)
{
    unsigned long c = crc;
    int i;
    if(!crc_table_computed){
        calcul_table_crc();
    }
    for(i=0; i<len; i++){
        c=crc_table[(c ^ dataCHUNK[i]) & 0xff] ^ (c >> 8);
    }
    return c;
}

//Fonction de calcul  du crc proprement dite, c'est celle ci au'il faudra appeller
unsigned long crc(unsigned char *dataChunk, int len)
{
    return maj_crc(0xffffffffL, dataChunk, len) ^  0xffffffffL;
}
