/**
 * @file Plateau.c
 * @brief Fonctions concernant le Plateau
 */

#include <stdio.h>
#include <stdlib.h>

#include "include/Couleur.h"
#include "include/Plateau.h"

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
  int taille,ancienneTaille,i,j;

  Matrice_getTaille(plateau,&taille,NULL);
  Matrice_getTaille(ancienPlateau,&ancienneTaille,NULL);

  if(taille != ancienneTaille)
	  return 0;

  for(i=0;i<taille;i++)
    for(j=0;j<taille;j++)
      if(Matrice_get(plateau,i,j) != Matrice_get(ancienPlateau,i,j))
	return 0;

  return 1;	  
}

int Plateau_copier(Plateau from, Plateau to)
{
  int i,j,taille,tailleTo;

  Matrice_getTaille(from,&taille,NULL);
  Matrice_getTaille(to,&tailleTo,NULL);

  if(taille != tailleTo)
	  return 0;

  for(i=0;i<taille;i++)
    for(j=0;j<taille;j++)
      Matrice_set(to, i, j, Matrice_get(from, i, j) );

  return 1;
}

void Plateau_sauvegarder(Plateau plateau,FILE* fichier)
{
  int i,j,taille;
  Couleur c;

  Matrice_getTaille(plateau,&taille,NULL);

  fwrite(&taille,sizeof(int),1,fichier);

  for(i=0;i<taille;i++)
    for(j=0;j<taille;j++)
    {
    	c = Matrice_get(plateau,i,j);
      fwrite(&c, sizeof(char), 1, fichier);
    }
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
