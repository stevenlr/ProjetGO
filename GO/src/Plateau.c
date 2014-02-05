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
#include "include/Territoire.h"

/**
 * Un goban
 */
struct Plateau {
	Matrice m;		//!< La matrice représentant le plateau.
	int nbPions[6]; //!< Nombre pions de chaque couleur. (Pour comparaison rapide des plateaux)
};

// Fonctions privées ==========================================================

static int Plateau_determinerSiEstOeil(Plateau plateau, Position position, Chaine chaine)
{
	int x, y, taille, nbChaine = 1;
	Chaine chaine2 =  NULL;

	Matrice_getTaille(plateau->m, NULL, &taille);

	x = Position_getX(position);
	y = Position_getY(position);

	// Haut
	Position_setY(position, --y);
	if(y >= 0)
	{
		if(!Chaine_appartient(chaine, position))
			return 0;
		else
			if(Plateau_get(plateau, position) == Chaine_getCouleur(chaine) && nbChaine != 2)
			{
				chaine2 = Plateau_determinerChaine(plateau, position);
				nbChaine++;
			}
			else
				return 0;	//!< La case est de couleur vide ou blanche
	}

	// Gauche
	Position_setY(position, ++y);
	Position_setX(position, --x);
	if(x >= 0)
		if(!Chaine_appartient(chaine, position))
		{
			if(nbChaine == 2 && !Chaine_appartient(chaine2, position))
			{
				Chaine_vider(chaine2);
				Chaine_detruire(chaine2);
				return 0;
			}
			else
				if(nbChaine != 2 && Plateau_get(plateau, position) == Chaine_getCouleur(chaine))
				{
					chaine2 = Plateau_determinerChaine(plateau, position);
					nbChaine++;
				}
				else
				{
					if(nbChaine == 2)
					{
						Chaine_vider(chaine2);
						Chaine_detruire(chaine2);
					}
					return 0;
				}
		}

	// Bas
	Position_setY(position, ++y);
	Position_setX(position, ++x);
	if(y < taille)
		if(!Chaine_appartient(chaine, position))
		{
			if(nbChaine == 2 && !Chaine_appartient(chaine2, position))
			{
				Chaine_vider(chaine2);
				Chaine_detruire(chaine2);
				return 0;
			}
			else
				if(nbChaine != 2 && Plateau_get(plateau, position) == Chaine_getCouleur(chaine))
				{
					chaine2 = Plateau_determinerChaine(plateau, position);
					nbChaine++;
				}
				else
				{
					if(nbChaine == 2)
					{
						Chaine_vider(chaine2);
						Chaine_detruire(chaine2);
					}
					return 0;
				}
		}

	// Droite
	Position_setY(position, --y);
	Position_setX(position, ++x);
	if(x < taille)
		if(!Chaine_appartient(chaine, position))
		{
			if(nbChaine == 2 && !Chaine_appartient(chaine2, position))
			{
				Chaine_vider(chaine2);
				Chaine_detruire(chaine2);
				return 0;
			}
			else
				if(nbChaine != 2 && Plateau_get(plateau, position) == Chaine_getCouleur(chaine))
				{
					chaine2 = Plateau_determinerChaine(plateau, position);
					nbChaine++;
				}
				else
				{
					if(nbChaine == 2)
					{
						Chaine_vider(chaine2);
						Chaine_detruire(chaine2);
					}
					return 0;
				}
		}

	Position_setX(position, --x);

	return 1;
}

// Fonctions publiques ========================================================

Plateau Plateau_creer(int taille)
{
	Plateau plateau = malloc(sizeof(struct Plateau));

	if(plateau == NULL)
		return NULL;

	plateau->m = Matrice_creer(taille, taille, VIDE);

	if(plateau->m == NULL)
	{
		free(plateau);
		return NULL;
	}

	plateau->nbPions[VIDE] = taille * taille;
	plateau->nbPions[NOIR] = 0;
	plateau->nbPions[BLANC] = 0;
	plateau->nbPions[AURANOIR] = 0;
	plateau->nbPions[AURABLANC] = 0;
	plateau->nbPions[AURAVIDE] = 0;

	return plateau;
}

void Plateau_detruire(Plateau plateau)
{
	assert(plateau);

	Matrice_detruire(plateau->m);
	free(plateau);
}

Couleur Plateau_get(Plateau plateau, Position pos)
{
	assert(plateau);

	return Matrice_get(plateau->m, Position_getY(pos), Position_getX(pos));
}

int Plateau_getTaille(Plateau plateau)
{
	int taille;

	assert(plateau);

	Matrice_getTaille(plateau->m, &taille, NULL);

	return taille;
}

void Plateau_set(Plateau plateau, Position pos, Couleur couleur)
{
	Couleur ancien;

	assert(plateau);

	ancien = Matrice_get(plateau->m, Position_getY(pos), Position_getX(pos));
	Matrice_set(plateau->m, Position_getY(pos), Position_getX(pos), couleur);

	plateau->nbPions[ancien]--;
	plateau->nbPions[couleur]++;
}

int Plateau_estIdentique(Plateau plateau, Plateau ancienPlateau)
{
	int taille, ancienneTaille, i, j;

	assert(plateau && ancienPlateau);

	Matrice_getTaille(plateau->m, &taille, NULL);
	Matrice_getTaille(ancienPlateau->m, &ancienneTaille, NULL);

	if(taille != ancienneTaille)
		return 0;

	for(i = 0; i < 6; i++)
	{
		if(plateau->nbPions[i] != ancienPlateau->nbPions[i])
			return 0;
	}

	for(i = 0; i < taille; i++)
		for(j = 0; j < taille; j++)
			if(Matrice_get(plateau->m, i, j) != Matrice_get(ancienPlateau->m, i, j))
				return 0;

	return 1;
}

Plateau Plateau_copier(Plateau from)
{
	int i, j, taille;
	Plateau to;
	Couleur c;

	assert(from);

	Matrice_getTaille(from->m, &taille, NULL);

	to = Plateau_creer(taille);

	if(to == NULL)
		return NULL;

	for(i = 0; i < taille; i++)
		for(j = 0; j < taille; j++)
		{
			c = Matrice_get(from->m, i, j),
			Matrice_set(to->m, i, j, c);
			to->nbPions[VIDE]--;
			to->nbPions[c]++;
		}

	return to;
}

void Plateau_sauvegarder(Plateau plateau, FILE* fichier)
{
	int i, j, taille;
	Couleur c;

	assert(plateau);

	Matrice_getTaille(plateau->m, &taille, NULL);

	fwrite(&taille, sizeof(int), 1, fichier);

	for(i = 0; i < taille; i++)
		for(j = 0; j < taille; j++)
		{
			c = Matrice_get(plateau->m, i, j);
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
			Matrice_set(plateau->m, i, j, c);
			plateau->nbPions[VIDE]--;
			plateau->nbPions[c]++;
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
	Matrice_getTaille(plateau->m, NULL, &taille);

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
	Pile_detruire(pile);

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

	if(Chaines_positionAppartient(chaines, position))
		return;

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
			*valide = 0;
		else
			*valide = 1;

		Chaine_vider(chaine);
		Chaine_detruire(chaine);

		Libertes_vider(libertes);
		Liste_detruire(libertes);
	}
	else
		*valide = 1;

	Position_detruire(debutChaine);

	return chaines;
}

Positions Plateau_determinerYeux(Plateau plateau, Chaine chaine)
{
	Positions positions;
	Libertes libertes;
	Position position;

	libertes = Libertes_determinerLibertes(plateau, chaine);
	positions = Liste_creer();

	if(libertes == NULL)
		return NULL;

	Liste_tete(libertes);

	do
	{
		position = Liste_courant(libertes);

		if(Plateau_determinerSiEstOeil(plateau, position, chaine))
			Liste_insererCourant(positions, Position_copier(position));

		Liste_supprimerCourant(libertes);
		Position_detruire(position);

	} while(!Liste_estVide(libertes));

	Liste_detruire(libertes);

	return positions;
}
