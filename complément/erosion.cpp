//erosion.cpp : Supprimer les points isolés

#include<stdio.h>
#include "image_ppm.h"

int main(int argc,char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille;

  if (argc != 3)
    {
      printf("Usage: ImageIn.pgm ImageOut.pgm \n");
      exit(1);
    }

   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgEcrite);

   OCTET *ImgIn, *ImgOut;
   
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
  
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille);
	
   //   for (int i=0; i < nTaille; i++)
   // {
   //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
   //  }
    // si objet (blanc,255) et que entouré de fond (noir,0) alors devient fond(noir,0)
    // donc si objet (blanc,255) et qu'un voisin est objet(blanc,255) alors reste objet(blanc,255) sinon devient fond(noir,0)


 for (int i=1; i < nH-1; i++)
   {
   for (int j=1; j < nW-1; j++)
     {
       if (ImgIn[i*nW+j]==255)
	     {
	        if (ImgOut[i*nW+j+1]==255)
	       { ImgOut[i*nW+j]=255;
	       }
	        else if (ImgIn[i*nW+j-1]==255)
	       { ImgOut[i*nW+j]=255;
	       }
	        else if (ImgIn[(i+1)*nW+j]==255)
	       { ImgOut[i*nW+j]=255;
	       }
	        else if (ImgIn[(i-1)*nW+j]==255)
	       { ImgOut[i*nW+j]=255;
	       }
	        else if (ImgIn[(i+1)*nW+j+1]==255)
	       { ImgOut[i*nW+j]=255;
	       }
	         else if (ImgIn[(i+1)*nW+j-1]==255)
	       { ImgOut[i*nW+j]=255;
	       }
	        else if (ImgIn[(i-1)*nW+j-1]==255)
	       { ImgOut[i*nW+j]=255;
	       }
	       else if (ImgIn[(i-1)*nW+j+1]==255)
	       { ImgOut[i*nW+j]=255;
	       }
         else
         { ImgOut[i*nW+j]=0;
         }
	     }     
       else ImgOut[i*nW+j]=0;
     }
   }

   ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
   free(ImgIn); free(ImgOut);

   return 1;
}
