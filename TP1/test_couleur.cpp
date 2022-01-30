// test_couleur.cpp : Seuille une image couleur 
#include <stdio.h>
#include <fstream>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.ppm\n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;

    int tableauR[256];
    int tableauG[256];
    int tableauB[256];
    for (int i=0;i<256;i++)
    {
        tableauR[i]= 0;
        tableauG[i]= 0;
        tableauB[i]= 0;
    }


   OCTET *ImgIn;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
    
   for (int i=0; i < nTaille3; i+=3)
     {
       tableauR[ImgIn[i]]++;
       tableauG[ImgIn[i+1]]++;
       tableauB[ImgIn[i+2]]++;
     }

   free(ImgIn);


   std::ofstream fichier {"histocoul.dat"};

   for (int i=0;i<256;i++)
   {
       fichier <<i<<"\t"<<tableauR[i]<<"\t"<<tableauG[i]<<"\t"<<tableauB[i]<<"\n"; 
   }

   fichier.close();

   return 1;
}
