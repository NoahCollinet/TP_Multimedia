// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImgEcrite[250], Y[250], Cb[250], Cr[250];
  int nH, nW, nTaille;
  
  if (argc != 5) 
     {
       printf("Usage: Y.pgm Cb.pgm Cr.pgm ImageOut.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",Y);
   sscanf (argv[2],"%s",Cb);
   sscanf (argv[3],"%s",Cr);
   sscanf (argv[4],"%s",cNomImgEcrite);
   

   OCTET *ImgInY, *ImgInCb, *ImgInCr, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(Y, &nH, &nW);
   nTaille = nH * nW;
  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgInY, OCTET, nTaille);
   lire_image_pgm(Y, ImgInY, nH * nW);
   allocation_tableau(ImgInCb, OCTET, nTaille);
   lire_image_pgm(Cb, ImgInCb, nH * nW);
   allocation_tableau(ImgInCr, OCTET, nTaille);
   lire_image_pgm(Cr, ImgInCr, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	int taille=0;
   for (int i=0; i < nTaille3; i+=3)
     {
       ImgOut[i]=(ImgInY[taille]+1.402*(ImgInCr[taille]-128))>255 ? 255 : (ImgInY[taille]+1.402*(ImgInCr[taille]-128))<0 ? 0 :ImgInY[taille]+1.402*(ImgInCr[taille]-128);
       ImgOut[i+1]=(ImgInY[taille]+1.772*(ImgInCb[taille]-128))>255? 255 : (ImgInY[taille]+1.772*(ImgInCb[taille]-128))<0? 0 : ImgInY[taille]+1.772*(ImgInCb[taille]-128);
       ImgOut[i+2]=(ImgInY[taille]-0.34414*(ImgInCb[taille]-128)-0.714414*(ImgInCr[taille]-128))>255? 255 : ImgInY[taille]-0.34414*(ImgInCb[taille]-128)-0.714414*(ImgInCr[taille]-128)<0? 0 : ImgInY[taille]-0.34414*(ImgInCb[taille]-128)-0.714414*(ImgInCr[taille]-128);
       taille++;   
     }
   ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgInY);free(ImgInCb);free(ImgInCr);free(ImgOut);
   return 1;
}
