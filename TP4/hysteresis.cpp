//hysteresis.cpp
#include <stdio.h>
#include <fstream>
#include <math.h>
#include "image_ppm.h"


int main(int argc, char*argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, SB, SH;

   if (argc!=5)
    {
      printf("Usage : ImageIn.pgm ImgOut.pgm seuil \n");
      exit(1) ;
    }
  sscanf(argv[1],"%s",cNomImgLue) ;
  sscanf(argv[2],"%s",cNomImgEcrite) ;
  sscanf(argv[3],"%d",&SB);
  sscanf(argv[4],"%d",&SH);
  
  OCTET *ImgIn, *ImgOut,*ImgTemp;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue,&nH,&nW);
  nTaille = nH*nW ;

  allocation_tableau(ImgIn, OCTET, nTaille);
  allocation_tableau(ImgTemp, OCTET, nTaille);
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
          
          if (ImgIn[i*nW+j]<=SB)
          {
            ImgTemp[i*nW+j]=0;
          }
          else if (ImgIn[i*nW+j]>=SH)
          {
              ImgTemp[i*nW+j]=255;
          }
          else 
          {
              ImgTemp[i*nW+j]=ImgIn[i*nW+j];
          }
      }
  }

  for (int i=0;i<nW-1;i++) {
      for (int j=0;j<nH-1;j++) {
          bool trouve=false;

          if (ImgTemp[i*nW+j+1]==255)
	       { trouve=true;
	       }
	        else if (ImgTemp[i*nW+j-1]==255)
	       { trouve=true;
	       }
	        else if (ImgTemp[(i+1)*nW+j]==255)
	       { trouve=true;
	       }
	        else if (ImgTemp[(i-1)*nW+j]==255)
	       { trouve=true;
	       }
	        else if (ImgTemp[(i+1)*nW+j+1]==255)
	       { trouve=true;
	       }
	         else if (ImgTemp[(i+1)*nW+j-1]==255)
	       { trouve=true;
	       }
	        else if (ImgTemp[(i-1)*nW+j-1]==255)
	       { trouve=true;
	       }
	       else if (ImgTemp[(i-1)*nW+j+1]==255)
	       { trouve=true;
	       }
          

          if (ImgTemp[i*nW+j]>SB && ImgTemp[i*nW+j]<SH && trouve)
          {
              ImgOut[i*nW+j]=255;
          }

          else if (ImgTemp[i*nW+j]>SB && ImgTemp[i*nW+j]<SH)
          {
              ImgOut[i*nW+j]=0;
          }

          else{
              ImgOut[i*nW+j]=ImgTemp[i*nW+j];
              }
      }
      
    }
  
  ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
    free(ImgIn); free(ImgOut);

  return 1;
}


	    
  

  
