//moyenneur.cpp : Filtre moyenneur
#include <cstdlib>
#include "image_ppm.h"

int main(int argc, char *argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;
  
    if (argc != 3) {
        printf("Utilisation : %s ImageIn.pgm ImageOut.pgm\n", argv[0]);
        exit(1);
    }

    sscanf(argv[1],"%s",cNomImgLue) ;
    sscanf(argv[2],"%s",cNomImgEcrite) ;
  
    OCTET *ImgIn, *ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue,&nH,&nW);
    nTaille = nH*nW ;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH*nW);
    allocation_tableau(ImgOut, OCTET, nTaille);


    for(int i=0; i<nH; i++) {
        for(int j=0; j<nW; j++) {
            int somme = 0;
            int quantite = 0;
            for(int a=-1; a<2; a++) {
                for(int b=-1; b<2; b++) {
                    if(i+a>=0 && i+a<nH && j+b>=0 && j+b<nW) {
                        somme += ImgIn[(i+a)*nW+j+b];
                        quantite++;
                    }
                }
            }
            ImgOut[i*nW+j] = (int)(somme/quantite);
        }
    }


    ecrire_image_pgm(argv[2], ImgOut, nH, nW);


    free(ImgIn); free(ImgOut);
    return 1;
}
