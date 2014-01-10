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
#include "include/Pion.h"

// Fonctions privées ==========================================================

/**
 * Ce nom c'est de la merde, mais on s'en tape parce que c'est une fonction privée.
 * Insère un pion dans la chaîne si :
 *  - Il est de la même couleur;
 *  - Il n'est pas déjà dans la chaîne.
 *
 * @param plateau
 * @param position
 * @param chaine
 * @param couleur Couleur de la chaîne.
 * @return Le pion, si on en a besoin. NULL sinon.
 */
static Pion Plateau_creerPionSiAppartientChaine(Plateau plateau, Position position, Chaine chaine, Couleur couleur)
{
	Pion pion = Pion_creer(position, Plateau_get(plateau, position));

	if(Pion_getCouleur(pion) == couleur && !(Chaine_appartient(chaine, pion)))
	{
		Chaine_inserer(chaine, pion);
		return pion;
	}

	Pion_detruire(pion);

	return NULL;
}

// Fonctions publiques ========================================================

Plateau Plateau_creer(int taille)
{
	return Matrice_creer(taille, taille, VIDE);
}

void Plateau_detruire(Plateau plateau)
{
	assert(plateau);

	Matrice_detruire(plateau);
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

Chaine Plateau_determinerChaine(Plateau plateau, Position origine)
{
	Chaine chaine;
	Pile pile;
	Pion pion, pionChaine;
	Position position;
	Couleur couleur;
	int taille;

	if((pile = Pile_creer()) == NULL)
		return NULL;

	if((chaine = Chaine_creer()) == NULL)
		return NULL;


	pionChaine = Pion_creer(origine, Plateau_get(plateau, origine));
	Matrice_getTaille(plateau, NULL, &taille);

	if(Pion_getCouleur(pionChaine) == VIDE)
		return NULL;

	Chaine_inserer(chaine, pionChaine);
	Pile_empiler(pile, pionChaine);

	couleur = Pion_getCouleur(pionChaine);

	while((pionChaine = Pile_depiler(pile)) != NULL)
	{
		position = Pion_getPosition(pionChaine);

		// Cas 1, en haut
		position.y -= 1;
		if(position.y >= 0)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, chaine, couleur);

			if(pion != NULL) // Si on l'a inséré à la chaîne, on devra le traiter plus tard.
				Pile_empiler(pile, pion);
		}

		// Cas 2, à droite
		position.y += 1;
		position.x += 1;
		if(position.x < taille)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, chaine, couleur);

			if(pion != NULL)
				Pile_empiler(pile, pion);
		}

		// Cas 3, en bas
		position.y += 1;
		position.x -= 1;
		if(position.y < taille)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, chaine, couleur);

			if(pion != NULL)
				Pile_empiler(pile, pion);
		}

		// Cas 4, à gauche
		position.y -= 1;
		position.x -= 1;
		if(position.x >= 0)
		{
			pion = Plateau_creerPionSiAppartientChaine(plateau, position, chaine, couleur);

			if(pion != NULL)
				Pile_empiler(pile, pion);
		}

	}

	return chaine;
}
