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
#include "include/Libertes.h"

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

	return Matrice_get(plateau, Position_getY(pos), Position_getX(pos));
}

int Plateau_getTaille(Plateau plateau)
{
	int taille;

	assert(plateau);

	Matrice_getTaille(plateau, &taille, NULL);

	return taille;
}

void Plateau_set(Plateau plateau, Position pos, Couleur couleur)
{
	assert(plateau);

	Matrice_set(plateau, Position_getY(pos), Position_getX(pos), couleur);
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
			Matrice_set(plateau, i, j, c);
		}

	return plateau;
}

Chaine Plateau_determinerChaine(Plateau plateau, Position origine)
{
	Chaine chaine;
	Pile pile;
	Position position;
	Couleur couleur;
	int taille, x, y;

	if((pile = Pile_creer()) == NULL)
		return NULL;

	if((chaine = Chaine_creer()) == NULL)
		return NULL;

	couleur = Plateau_get(plateau, origine);
	Matrice_getTaille(plateau, NULL, &taille);

	if(couleur == VIDE)
		return NULL;

	Chaine_inserer(chaine, Position_copier(origine));
	Pile_empiler(pile, Position_copier(origine));

	while((position = Pile_depiler(pile)) != NULL)
	{
		x = Position_getX(position);
		y = Position_getY(position);

		// Cas 1, en haut
		Position_setY(position, --y);
		if(y >= 0)
		{
			if(Plateau_get(plateau, position) == couleur && !(Chaine_appartient(chaine, position)))
			{
				Chaine_inserer(chaine, Position_copier(position));
				Pile_empiler(pile, Position_copier(position));
			}
		}

		// Cas 2, à droite
		Position_setX(position, ++x);
		Position_setY(position, ++y);
		if(x < taille)
		{
			if(Plateau_get(plateau, position) == couleur && !(Chaine_appartient(chaine, position)))
			{
				Chaine_inserer(chaine, Position_copier(position));
				Pile_empiler(pile, Position_copier(position));
			}
		}

		// Cas 3, en bas
		Position_setX(position, --x);
		Position_setY(position, ++y);
		if(y < taille)
		{
			if(Plateau_get(plateau, position) == couleur && !(Chaine_appartient(chaine, position)))
			{
				Chaine_inserer(chaine, Position_copier(position));
				Pile_empiler(pile, Position_copier(position));
			}
		}

		// Cas 4, à gauche
		Position_setX(position, --x);
		Position_setY(position, --y);
		if(x >= 0)
		{
			if(Plateau_get(plateau, position) == couleur && !(Chaine_appartient(chaine, position)))
			{
				Chaine_inserer(chaine, Position_copier(position));
				Pile_empiler(pile, Position_copier(position));
			}
		}

		Position_detruire(position);
	}

	Chaine_setCouleur(chaine, couleur);

	return chaine;
}

void Plateau_realiserCapture(Plateau plateau, Chaine chaine)
{
	Position position;

	if(Chaine_estVide(chaine))
		return;

	Chaine_tete(chaine);

	do
	{
		position = Chaine_courant(chaine);
		Plateau_set(plateau, position, VIDE);
	} while(Chaine_suivant(chaine));
}

/**
 * Ajoute la chaine commençant à position à chaines si elle n'a plus de libertées.
 *
 * @param plateau
 * @param position
 * @param chaines
 */
static void Plateau_estCapturable(Plateau plateau, Position position, Chaines chaines)
{
	Chaine chaine;
	Libertes libertes;

	chaine = Plateau_determinerChaine(plateau, position);
	libertes = Libertes_determinerLibertes(plateau, chaine);

	if(Liste_estVide(libertes))
	{
		Liste_insererQueue(chaines, chaine);
	}
	else
	{
		Chaine_vider(chaine);
		Chaine_detruire(chaine);
	}

	Libertes_vider(libertes);
	Liste_detruire(libertes);
}

Chaines Plateau_capturerChaines(Plateau plateau, Pion pion, int* valide)
{
	Chaine chaine;
	Libertes libertes;
	Chaines chaines;
	Position position, debutChaine;
	Couleur couleur, aCapturer;
	int x, y, taille;

	assert(plateau && pion);

	position = Pion_getPosition(pion);
	couleur = Pion_getCouleur(pion);

	Plateau_set(plateau, position, couleur);
	taille = Plateau_getTaille(plateau);

	if(couleur == VIDE)
	{
		*valide = 0;
		return NULL;
	}

	x = Position_getX(position);
	y = Position_getY(position);

	debutChaine = Position_creer(x, y);

	aCapturer = (couleur == NOIR) ? BLANC : NOIR;

	chaines = Liste_creer();

	if(chaines == NULL)
		return NULL;

	// Haut
	Position_setY(debutChaine, --y);
	if(y >= 0)
		if(Plateau_get(plateau, debutChaine) == aCapturer)
			Plateau_estCapturable(plateau, debutChaine, chaines);

	// Gauche
	Position_setY(debutChaine, ++y);
	Position_setX(debutChaine, --x);
	if(x >= 0)
		if(Plateau_get(plateau, debutChaine) == aCapturer)
			Plateau_estCapturable(plateau, debutChaine, chaines);

	// Bas
	Position_setY(debutChaine, ++y);
	Position_setX(debutChaine, ++x);
	if(y < taille)
		if(Plateau_get(plateau, debutChaine) == aCapturer)
			Plateau_estCapturable(plateau, debutChaine, chaines);

	// Droite
	Position_setY(debutChaine, --y);
	Position_setX(debutChaine, ++x);
	if(x < taille)
		if(Plateau_get(plateau, debutChaine) == aCapturer)
			Plateau_estCapturable(plateau, debutChaine, chaines);

	if(Liste_estVide(chaines))
	{
		chaine = Plateau_determinerChaine(plateau, position);
		libertes = Libertes_determinerLibertes(plateau, chaine);

		if(Liste_estVide(libertes))
		{
			*valide = 0;
		}
		else
		{
			Chaine_vider(chaine);
			Chaine_detruire(chaine);
			*valide = 1;
		}

		Libertes_vider(libertes);
		Liste_detruire(libertes);
	}
	else
		*valide = 1;

	Position_detruire(debutChaine);

	return chaines;
}
