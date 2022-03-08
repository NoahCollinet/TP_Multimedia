#include <stdio.h>
#include <fstream>
#include "image_ppm.h"

int main(int argc, char*argv[])
{
  char cNomImgLue[250], info;
  int nH, nW, nTaille, indice;

   if (argc!=4)
    {
      printf("Usage : ImageIn.pgm info indice \n");
      exit(1) ;
    }
  sscanf(argv[1],"%s",cNomImgLue) ;
  sscanf(argv[2],"%s",&info) ;
  sscanf(argv[3],"%i",&indice) ;
  
  OCTET *ImgIn;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue,&nH,&nW);
  nTaille = nH*nW ;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH*nW);

  if (info=='c')
    {
      int tableau[nW];

      for (int j=0; j<nW ; j++)
	{
	  tableau[j] = ImgIn[indice*nW+j];
	}
       std::ofstream fichier ("profil.dat");

      for (int i=0; i<nW; i++){
	fichier <<i<<"\t"<<tableau[i]<<"\n";
      }
      fichier.close();
    }

  else
    {
      int tab[nH];

      for (int i=0; i<nH ; i++)
	{
	  tab[i] = ImgIn[i*nW+indice];
	}
      std::ofstream fichier ("profil.dat");

      for (int i=0; i<nH; i++){
	fichier <<i<<"\t"<<tab[i]<<"\n";
      }
      fichier.close();
    }
  
}


	    
  

  
