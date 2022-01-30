

    // seuil_couleur.cpp : Seuille une image couleur 

    #include <stdio.h>
    #include "image_ppm.h"

    int main(int argc, char* argv[])
    {
      char cNomImgLue[250], cNomImgEcrite[250];
      int nH, nW, nTaille, nR, nG, nB, SR, SG, SB;
      
      if (argc != 6) 
         {
           printf("Usage: ImageIn.ppm ImageOut.ppm SR SG SB \n"); 
           exit (1) ;
         }
       
       sscanf (argv[1],"%s",cNomImgLue) ;
       sscanf (argv[2],"%s",cNomImgEcrite);
       sscanf (argv[3],"%d",&SR);
       sscanf (argv[4],"%d",&SG);
       sscanf (argv[5],"%d",&SB);

       OCTET *ImgIn, *ImgOut;
       
       lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
       nTaille = nH * nW;
      
       int nTaille3 = nTaille * 3;
       allocation_tableau(ImgIn, OCTET, nTaille3);
       lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
       allocation_tableau(ImgOut, OCTET, nTaille3);
        
       for (int j=0; j < nTaille3; j+=3)
         {
           nR = ImgIn[j];
           nG = ImgIn[j+1];
           nB = ImgIn[j+2];
           if (nR < SR) ImgOut[j]=0; else ImgOut[j]=255;
           if (nG < SG) ImgOut[j+1]=0; else ImgOut[j+1]=255; 
           if (nB < SB) ImgOut[j+2]=0; else ImgOut[j+2]=255;
         }

       ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
       free(ImgIn);
       return 1;
    }

