//norme_gradient.cpp
#include <stdio.h>
#include <fstream>
#include <math.h>
#include "image_ppm.h"


int main(int argc, char*argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

   if (argc!=3)
    {
      printf("Usage : ImageIn.pgm ImgOut.pgm \n");
      exit(1) ;
    }
  sscanf(argv[1],"%s",cNomImgLue) ;
  sscanf(argv[2],"%s",cNomImgEcrite) ;
  
  OCTET *ImgIn, *ImgOut;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue,&nH,&nW);
  nTaille = nH*nW ;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH*nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  int Gx;
  int Gy;

  /*for (int k=0; k<256;k++)
  {
      Gx[k]=0;
      Gy[k]=0;  
  }*/

  for (int i=0;i<nW-1;i++) {
      for (int j=0;j<nH-1;j++) {
          Gx=-1*ImgIn[i*nW+j]+ImgIn[(i+1)*nW+j];
          Gy=-1*ImgIn[i*nW+j]+ImgIn[i*nW+j+1];
          ImgOut[i*nW+j]=sqrt((Gx*Gx) + (Gy*Gy));
      }
  }
  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut);

  return 1;
}


	    
  

  
