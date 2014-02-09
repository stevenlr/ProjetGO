/**
 * @file Territoire.c
 */

#include <stdlib.h>

#include "include/Territoire.h"
#include "include/Plateau.h"
#include "include/Chaine.h"
#include "include/Position.h"
#include "include/Pile.h"
#include "include/Pion.h"
#include "include/Couleur.h"
#include "include/Libertes.h"

// Fonctions privées ==========================================================

static void Territoire_determinerCouleur(Couleur couleur, Territoire territoire, int *estNeutre)
{
	if(*estNeutre == 0 && couleur != VIDE)
	{
		if(Chaine_getCouleur(territoire) == VIDE)
		{
			Chaine_setCouleur(territoire, couleur);
		}
		else if(couleur != Chaine_getCouleur(territoire))
		{
			Chaine_setCouleur(territoire, VIDE);
			*estNeutre = 1;
		}
	}
}

// Fonctions publiques ========================================================

Territoire Territoire_determinerTerritoire(Plateau plateau, Position origine)
{
	Territoire territoire;
	Pile pile;
	Position position;
	int taille, x, y, estNeutre = 0, i, ox, oy;
	int decalages[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	Couleur couleur;

	if((pile = Pile_creer()) == NULL)
		return NULL;

	if((territoire = Chaine_creer()) == NULL)
	{
		Pile_detruire(pile);
		return NULL;
	}

	position = Position_copier(origine);
	taille = Plateau_getTaille(plateau);

	if(Plateau_get(plateau, origine) != VIDE)
	{
		Pile_detruire(pile);
		Chaine_detruire(territoire);
		Position_detruire(position);
		return NULL;
	}

	Chaine_inserer(territoire, Position_copier(position));
	Pile_empiler(pile, position);

	Chaine_setCouleur(territoire, VIDE);

	while((position = Pile_depiler(pile)) != NULL)
	{
		ox = Position_getX(position);
		oy = Position_getY(position);

		for(i = 0; i < 4; i++)
		{
			x = ox + decalages[i][0];
			y = oy + decalages[i][1];

			if(x < 0 || y < 0 || x >= taille || y >= taille)
				continue;

			Position_setX(position, x);
			Position_setY(position, y);

			couleur = Plateau_get(plateau, position);

			if(couleur == VIDE && !Chaine_appartient(territoire, position))
			{
				Chaine_inserer(territoire, Position_copier(position));
				Pile_empiler(pile, Position_copier(position));
			}

			Territoire_determinerCouleur(couleur, territoire, &estNeutre);
		}

		Position_detruire(position);
	}

	Pile_detruire(pile);

	return territoire;
}

Chaines Territoire_determinerChainesAutour(Territoire territoire, Plateau plateau)
{
	Chaines chaines;
	Chaine chaine;
	Position origine, position;
	int x, y, taille, i, ox, oy;
	int decalages[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	if(Chaine_estVide(territoire))
		return NULL;

	chaines = Liste_creer();
	taille = Plateau_getTaille(plateau);
	position = Position_creer(0, 0);

	Chaine_tete(territoire);

	do
	{
		origine = Chaine_courant(territoire);
		ox = Position_getX(origine);
		oy = Position_getY(origine);

		for(i = 0; i < 4; i++)
		{
			x = ox + decalages[i][0];
			y = oy + decalages[i][1];

			if(x < 0 || y < 0 || y >= taille || x >= taille)
				continue;

			Position_setX(position, x);
			Position_setY(position, y);

			if(Plateau_get(plateau, position) != VIDE)
				if(!Chaines_positionAppartient(chaines, position))
				{
					chaine = Plateau_determinerChaine(plateau, position);
					Liste_insererCourant(chaines, chaine);
				}
		}

	} while(Chaine_suivant(territoire));

	Position_detruire(position);

	return chaines;
}

int Territoire_estUnSeki(Territoire territoire, Plateau plateau)
{
	Chaines chaines;
	Chaine chaine;
	Libertes libertes;
	Position position;
	int status = 1; // Histoire d'avoir le temps de libérer la mémoire.

	if(Chaine_getCouleur(territoire) !=  VIDE)
		return 0;

	if(Chaine_getNbElements(territoire) != 2)
		return 0;

	chaines = Territoire_determinerChainesAutour(territoire, plateau);

	do
	{
		chaine = Liste_courant(chaines);
		libertes = Libertes_determinerLibertes(plateau, chaine); // Forcément, il y a des libertés ce sont les chaînes qui entourent un territoire vide.

		do
		{
			position = Liste_courant(libertes);

			if(!Chaine_appartient(territoire, position)) // Si une liberté n'est pas dans le territoire dit Séki, il n'y a pas Séki.
				status = 0;

		} while(Liste_suivant(libertes) && !status);

		Libertes_vider(libertes);
		Liste_detruire(libertes);

		Chaine_vider(chaine);
		Chaine_detruire(chaine);

		Liste_supprimerCourant(chaines);

	} while(!Liste_estVide(chaines)); // On s'arrête pas quand status=0 car il faut désallouer toutes les choses !

	Liste_detruire(chaines);

	return status;
}

int Territoire_determinerNbCases(Territoire territoire)
{
	int n = 0;

	if(territoire == NULL)
		return 0;

	Chaine_tete(territoire);

	do
	{
		n++;
	} while(Chaine_suivant(territoire));

	return n;
}

