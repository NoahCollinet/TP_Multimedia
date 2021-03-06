//gaussien.cpp : Filtre gaussien
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


    for (int i = 0; i < nH; ++i) {
        for (int j = 0; j < nW; ++j) {

            if (i == 0 || j == 0 || i == nH - 1 || j == nW - 1) {
                ImgOut[i*nH + j] = ImgIn[i*nH + j];
            }
            else {
                int sum = 0;

                for (int k = -1; k <= 1; ++k) {
                    for (int m = -1; m <= 1; ++m) {
                        int key = (i + k)*nW + (j + m);
                        int mul = 2*((k == 0) + (m == 0));
                        if (mul == 0) mul = 1;
                        sum += mul * ImgIn[key];
                    }
                }

                ImgOut[i*nH + j] = round(sum / 16);
            }
        }
    }


    ecrire_image_pgm(argv[2], ImgOut, nH, nW);


    free(ImgIn); free(ImgOut);
    return 1;
}
