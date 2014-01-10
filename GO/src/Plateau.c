/**
 * @file Plateau.c
 * @brief Fonctions concernant le Plateau
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "include/Position.h"
#include "include/Couleur.h"
#include "include/Chaine.h"
#include "include/Plateau.h"
#include "include/Pile.h"

Plateau Plateau_creer(int taille)
{
	return Matrice_creer(taille, taille, VIDE);
}

void Plateau_detruire(Plateau* plateau)
{
	assert(plateau && *plateau);

	Matrice_detruire(*plateau);
	*plateau = NULL;
}

Couleur Plateau_get(Plateau plateau, Position pos)
{
	assert(plateau);

	return Matrice_get(plateau, pos.x, pos.y);
}

void Plateau_set(Plateau plateau, int i, int j, Couleur couleur)
{
	assert(plateau);

	Matrice_set(plateau, i, j, couleur);
}

int Plateau_estIdentique(Plateau plateau, Plateau ancienPlateau)
{
	int taille, ancienneTaille, i, j;

	assert(plateau && ancienPlateau);

	Matrice_getTaille(plateau, &taille, NULL);
	Matrice_getTaille(ancienPlateau, &ancienneTaille, NULL);

	if(taille != ancienneTaille)
		return 0;

	for(i = 0; i < taille; i++)
		for(j = 0; j < taille; j++)
			if(Matrice_get(plateau, i, j) != Matrice_get(ancienPlateau, i, j))
				return 0;

	return 1;
}

Plateau Plateau_copier(Plateau from)
{
	int i, j, taille;
	Plateau to;

	assert(from);

	Matrice_getTaille(from, &taille, NULL);

	to = Plateau_creer(taille);

	if(to == NULL)
		return NULL;

	for(i = 0; i < taille; i++)
		for(j = 0; j < taille; j++)
			Matrice_set(to, i, j, Matrice_get(from, i, j));

	return to;
}

void Plateau_sauvegarder(Plateau plateau, FILE* fichier)
{
	int i, j, taille;
	Couleur c;

	assert(plateau);

	Matrice_getTaille(plateau, &taille, NULL);

	fwrite(&taille, sizeof(int), 1, fichier);

	for(i = 0; i < taille; i++)
		for(j = 0; j < taille; j++)
		{
			c = Matrice_get(plateau, i, j);
			putc(c, fichier);
		}
}

Plateau Plateau_charger(FILE* fichier)
{
	int i, j, taille;
	Plateau plateau;
	Couleur c;

	fread(&taille, sizeof(int), 1, fichier);

	plateau = Plateau_creer(taille);

	if(plateau == NULL)
		return NULL;

	for(i = 0; i < taille; i++)
		for(j = 0; j < taille; j++)
		{
			c = getc(fichier);
			Plateau_set(plateau, i, j, c);
		}

	return plateau;
}

Chaine Plateau_determinerChaine(Plateau plateau, Position pos)
{
	Chaine chaine = Chaine_creer();
	Pile pile = Pile_creer();
	int taille;
	Pion* pionChaine;
	Pion* pion;

	pionChaine = Pion_creer(pos, Plateau_get(plateau, pos) );
	Matrice_getTaille(plateau, NULL, &taille);

	if(pionChaine->couleur == VIDE)
		return NULL;

	Chaine_inserer(chaine, pionChaine);
	Pile_empiler(pile, pionChaine);

	while( (pionChaine = Pile_depiler(pile)) != NULL)
	{
		pos = pionChaine->position;

		// Cas 1, en haut
		pos.y -= 1;
		if(pos.y >= 0)
		{
			pion = Pion_creer(pos, Plateau_get(plateau, pos) );

			if(pion->couleur == pionChaine->couleur && ! (Chaine_appartenir(chaine, *pion)) )
			{
				Chaine_inserer(chaine, pion);
				Pile_empiler(pile, pion);
			}
		}

		// Cas 2, à droite
		pos.y += 1;
		pos.x += 1;
		if(pos.x < taille)
		{
			pion = Pion_creer(pos, Plateau_get(plateau, pos) );

			if(pion->couleur == pionChaine->couleur && ! (Chaine_appartenir(chaine, *pion)) )
			{
				Chaine_inserer(chaine, pion);
				Pile_empiler(pile, pion);
			}
		}

		// Cas 3, en bas
		pos.y += 1;
		pos.x -= 1;
		if(pos.y < taille)
		{
			pion = Pion_creer(pos, Plateau_get(plateau, pos) );

			if(pion->couleur == pionChaine->couleur && ! (Chaine_appartenir(chaine, *pion)) )
			{
				Chaine_inserer(chaine, pion);
				Pile_empiler(pile, pion);
			}
		}

		// Cas 4, à gauche
		pos.y -= 1;
		pos.x -= 1;
		if(pos.x >= 0)
		{
			pion = Pion_creer(pos, Plateau_get(plateau, pos) );

			if(pion->couleur == pionChaine->couleur && ! (Chaine_appartenir(chaine, *pion)) )
			{
				Chaine_inserer(chaine, pion);
				Pile_empiler(pile, pion);
			}
		}

	}

	return chaine;
}
