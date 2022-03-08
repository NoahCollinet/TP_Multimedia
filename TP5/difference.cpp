//difference.cpp : Dessine les contours selon l'image seuillée et l'image dilatée

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue1[250], cNomImgLue2[250], cNomImgEcrite[250];
  int nH, nW, nTaille, S;
  
  if (argc != 4){
    printf("Usage: ImageSeuillee.pgm ImageDilatee.pgm ImageOut.pgm \n"); 
    exit (1) ;
  }
   
  sscanf (argv[1],"%s",cNomImgLue1) ;
  sscanf (argv[2],"%s",cNomImgLue2) ;
  sscanf (argv[3],"%s",cNomImgEcrite);

  OCTET *ImgSeuil, *ImgDil, *ImgOut;
  
  lire_nb_lignes_colonnes_image_pgm(cNomImgLue1, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgSeuil, OCTET, nTaille);
  lire_image_pgm(cNomImgLue1, ImgSeuil, nH * nW);
  allocation_tableau(ImgDil, OCTET, nTaille);
  lire_image_pgm(cNomImgLue2, ImgDil, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille);

  //   for (int i=0; i < nTaille; i++)
  // {
  //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
  //  }


  for (int i=0; i < nH; i++)
    for (int j=0; j < nW; j++){
      if((j == 0)||(j == nW-1)||(i == 0)||(i == nH-1)){
        ImgOut[i*nW+j]=255;
      }  
      else if ((ImgSeuil[i*nW+j] == 255)&&(ImgDil[i*nW+j] == 255)){
        ImgOut[i*nW+j]=255;
      }
      else if ((ImgSeuil[i*nW+j] == 0)&&(ImgDil[i*nW+j] == 0)){
        ImgOut[i*nW+j]=255;
      }
      else {ImgOut[i*nW+j]=0;}
    }

  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
  free(ImgSeuil); free(ImgDil);
  return 1;
}