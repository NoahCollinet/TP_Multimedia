//difference.cpp : Contours d'une image

#include<stdio.h>
#include "image_ppm.h"

int main(int argc,char* argv[])
{
  char cNomImgLueS[250], cNomImgLueD[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc != 4)
    {
      printf("Usage: ImageInSeuil.pgm ImageInDilatee.pgm ImageOut.pgm \n");
      exit(1);
    }

   sscanf (argv[1],"%s",cNomImgLueS) ;
   sscanf (argv[2],"%s",cNomImgLueD);
   sscanf (argv[3],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLueS, &nHS, &nWS);
   lire_nb_lignes_colonnes_image_pgm(cNomImgLueS, &nHD, &nWD);
   nTailleS = nHS * nWS;
   nTailleD = nHD * nWD;
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	int caca=1;
}
//Si les deux pixels (de l’image seuillée et de l’image dilatée) appartiennent au fond
//alors le pixel correspondant de l’image de sortie appartiendra au fond (255).
//Si les deux pixels (de l’image seuillée et de l’image dilatée) appartiennent à l’objet
//alors le pixel correspondant de l’image de sortie appartiendra au fond (255).
//Sinon le pixel correspondant de l’image de sortie appartiendra au contour (0).


for (int i=0; i < nH; i++)
   {
   for (int j=0; j < nW; j++)
     { printf("%i caca="caca);
     caca++;
     }
   }
