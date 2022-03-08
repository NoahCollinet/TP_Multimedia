// RGBtoY.cpp : Transforme une image couleur en une image en niveaux de gris 

#include <stdio.h>
#include <string.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcriteY[250],cNomImgEcriteCb[250],cNomImgEcriteCr[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageOut\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcriteY);
   sscanf (argv[2],"%s",cNomImgEcriteCb);
   sscanf (argv[2],"%s",cNomImgEcriteCr);
   strcat(cNomImgEcriteY,"Y.pgm");
   strcat(cNomImgEcriteCb,"Cb.pgm");
   strcat(cNomImgEcriteCr,"Cr.pgm");
   OCTET *ImgIn, *ImgOutY, *ImgOutCb, *ImgOutCr;

   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
    int nTaille3=nTaille*3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOutY, OCTET, nTaille);
   allocation_tableau(ImgOutCb, OCTET, nTaille);
   allocation_tableau(ImgOutCr, OCTET, nTaille);
    
   int taille=0;
   for (int i=0; i < nTaille3; i+=3)
     {
       ImgOutY[taille]= 0.299*ImgIn[i]+0.587*ImgIn[i+1]+0.114*ImgIn[i+2];
       ImgOutCb[taille]= -0.1687*ImgIn[i]-0.3313*ImgIn[i+1]+0.5*ImgIn[i+2]+128;
       ImgOutCr[taille]= 0.5*ImgIn[i]-0.4187*ImgIn[i+1]+0.0813*ImgIn[i+2]+128; 
       taille++;   
     }
 

   ecrire_image_pgm(cNomImgEcriteY, ImgOutY,  nH, nW);
   ecrire_image_pgm(cNomImgEcriteCb, ImgOutCb,  nH, nW);
   ecrire_image_pgm(cNomImgEcriteCr, ImgOutCr,  nH, nW);
   free(ImgIn); free(ImgOutY);free(ImgOutCb);free(ImgOutCr); 

   return 1;
}
