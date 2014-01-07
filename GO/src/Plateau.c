
#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"

Plateau Plateau_creer(int taille)
{
  return Matrice_creer(taille,taille,VIDE);
}

void Plateau_detruire(Plateau plateau)
{
  Matrice_detruire(plateau);
}

Couleur Plateau_get(Plateau plateau, int i, int j)
{
  return Matrice_get(plateau,i,j);
}

void Plateau_set(Plateau plateau, int i, int j, Couleur couleur)
{
  Matrice_set(plateau,i,j,couleur);
}

int Plateau_estIdentique(Plateau plateau, Plateau ancienPlateau)
{
  int taille,i,j;

  Matrice_getTaille(plateau,&taille,NULL);

  for(i=0;i<taille;i++)
    for(j=0;j<taille;j++)
      if(Matrice_get(plateau,i,j) != Matrice_get(ancienPlateau,i,j))
	return 0;

  return 1;	  
}

void Plateau_copie(Plateau from, Plateau to)
{
  int i,j,taille;

  Matrice_getTaille(from,&taille,NULL);

  for(i=0;i<taille;i++)
    for(j=0;j<taille;j++)
      Matrice_set(to, i, j, Matrice_get(from, i, j) );
}

void Plateau_sauvegarde(Plateau plateau,FILE* fichier)
{
  int i,j,taille;

  Matrice_getTaille(plateau,&taille,NULL);

  fwrite(taille,sizeof(int),1,fichier);

  for(i=0;i<taille;i++)
    for(j=0;j<taille;j++)
      fwrite(Matrice_get(plateau,i,j), sizeof(char), 1, fichier);
}

Plateau Plateau_charger(FILE* fichier)
{
  int i,j,taille;
  Plateau plateau;
  Couleur c;

  fread(&taille, sizeof(int), 1, fichier);

  plateau = Plateau_creer(taille);

  for(i=0;i<taille;i++)
    for(j=0;j<taille;j++)
      {
	fread(&c, sizeof(char), 1, fichier);
	Plateau_set(plateau,i,j,c);
      }

  return plateau;
}
