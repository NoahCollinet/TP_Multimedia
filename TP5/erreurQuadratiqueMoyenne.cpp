// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char nomImg1[250], nomImg2[250];
  int nH, nW, nTaille;
  
  if (argc != 3) 
     {
       printf("Usage: ImageDeBase.pgm ImageObtenue.pgm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",nomImg1) ;
   sscanf (argv[2],"%s",nomImg2);

   OCTET *ImgIn, *ImgIn2;
   
   lire_nb_lignes_colonnes_image_pgm(nomImg1, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(nomImg1, ImgIn, nH * nW);
   allocation_tableau(ImgIn2, OCTET, nTaille);
   lire_image_pgm(nomImg2, ImgIn2, nH * nW);
    int erreur=0;
   for (int i=0; i < nTaille; i++)
     {
       erreur+=(ImgIn[i]-ImgIn2[i])*(ImgIn[i]-ImgIn2[i]);  
     }
    erreur/=nTaille;
   free(ImgIn);free(ImgIn2);
   printf("L'erreur quadratique moyenne est de: %i\n",erreur);
   return 1;
}
