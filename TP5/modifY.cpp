#include <stdio.h>
#include <string.h> 
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille,k;
  
  if (argc != 3) 
     {
       printf("Usage: Y(sans le .pgm) k(-128,128)\n"); 
       exit (1) ;
     }
   sscanf (argv[1],"%s",cNomImgLue);
   sscanf (argv[2],"%i",&k);
   sscanf (argv[1],"%s",cNomImgEcrite);
    strcat(cNomImgEcrite,"bis.pgm");
    strcat(cNomImgLue,".pgm");

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);

    for (int i=0; i < nH; i++){ 
    for (int j=0; j < nW; j++)
        {
        ImgOut[i*nW+j]=(ImgIn[i*nW+j]+k)<0? 0 : (ImgIn[i*nW+j]+k)>255? 255 : ImgIn[i*nW+j]+k;
        }
    } 


   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn);free(ImgOut);
   return 1;
}
