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

// Fonctions priv�es ==========================================================

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
	Position position, positionNouvelle;
	int taille, x, y, estNeutre = 0;
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
		x = Position_getX(position);
		y = Position_getY(position);

		// Cas 1, en haut
		y--;
		if(y >= 0)
		{
			positionNouvelle = Position_creer(x, y);
			couleur = Plateau_get(plateau, positionNouvelle);

			if(couleur == VIDE && !Chaine_appartient(territoire, positionNouvelle))
			{
				Chaine_inserer(territoire, Position_copier(positionNouvelle));
				Pile_empiler(pile, positionNouvelle);
			}
			else
				Position_detruire(positionNouvelle);

			Territoire_determinerCouleur(couleur, territoire, &estNeutre);
		}

		// Cas 2, � droite
		y++;
		x++;
		if(x < taille)
		{
			positionNouvelle = Position_creer(x, y);
			couleur = Plateau_get(plateau, positionNouvelle);

			if(couleur == VIDE && !Chaine_appartient(territoire, positionNouvelle))
			{
				Chaine_inserer(territoire, Position_copier(positionNouvelle));
				Pile_empiler(pile, positionNouvelle);
			}
			else
				Position_detruire(positionNouvelle);

			Territoire_determinerCouleur(couleur, territoire, &estNeutre);
		}

		// Cas 3, en bas
		y++;
		x--;
		if(y < taille)
		{
			positionNouvelle = Position_creer(x, y);
			couleur = Plateau_get(plateau, positionNouvelle);

			if(couleur == VIDE && !Chaine_appartient(territoire, positionNouvelle))
			{
				Chaine_inserer(territoire, Position_copier(positionNouvelle));
				Pile_empiler(pile, positionNouvelle);
			}
			else
				Position_detruire(positionNouvelle);

			Territoire_determinerCouleur(couleur, territoire, &estNeutre);
		}

		// Cas 4, � gauche
		y--;
		x--;
		if(x >= 0)
		{
			positionNouvelle = Position_creer(x, y);
			couleur = Plateau_get(plateau, positionNouvelle);

			if(couleur == VIDE && !Chaine_appartient(territoire, positionNouvelle))
			{
				Chaine_inserer(territoire, Position_copier(positionNouvelle));
				Pile_empiler(pile, positionNouvelle);
			}
			else
				Position_detruire(positionNouvelle);

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
	Position position;
	int x, y, taille;

	if(Chaine_estVide(territoire))
		return NULL;

	chaines = Liste_creer();
	taille = Plateau_getTaille(plateau);
	Chaine_tete(territoire);

	do
	{
		position = Chaine_courant(territoire);
		x = Position_getX(position);
		y = Position_getY(position);

		// Haut
		Position_setY(position, --y);
		if(y >= 0)
			if(Plateau_get(plateau, position) != VIDE)
				if(!Chaines_positionAppartient(chaines, position))
				{
					chaine = Plateau_determinerChaine(plateau, position);
					Liste_insererCourant(chaines, chaine);
				}

		// Gauche
		Position_setY(position, ++y);
		Position_setX(position, --x);
		if(x >= 0)
			if(Plateau_get(plateau, position) != VIDE)
				if(!Chaines_positionAppartient(chaines, position))
				{
					chaine = Plateau_determinerChaine(plateau, position);
					Liste_insererCourant(chaines, chaine);
				}

		// Bas
		Position_setY(position, ++y);
		Position_setX(position, ++x);
		if(y < taille)
			if(Plateau_get(plateau, position) != VIDE)
				if(!Chaines_positionAppartient(chaines, position))
				{
					chaine = Plateau_determinerChaine(plateau, position);
					Liste_insererCourant(chaines, chaine);
				}
		// Droite
		Position_setY(position, --y);
		Position_setX(position, ++x);
		if(x < taille)
			if(Plateau_get(plateau, position) != VIDE)
				if(!Chaines_positionAppartient(chaines, position))
				{
					chaine = Plateau_determinerChaine(plateau, position);
					Liste_insererCourant(chaines, chaine);
				}

	} while(Chaine_suivant(territoire));

	return chaines;
}

int Territoire_estUnSeki(Territoire territoire, Plateau plateau)
{
	Chaines chaines;
	Chaine chaine;
	Libertes libertes;
	Position position;
	int status = 1; // Histoire d'avoir le temps de lib�rer la m�moire.

	if(Chaine_getCouleur(territoire) !=  VIDE)
		return 0;

	if(Chaine_getNbElements(territoire) != 2)
		return 0;

	chaines = Territoire_determinerChainesAutour(territoire, plateau);

	do
	{
		chaine = Liste_courant(chaines);
		libertes = Libertes_determinerLibertes(plateau, chaine); //Forc�ment, il y a des libert�s vu que ce sont les chaines qui entourent un territoire vide.

		do
		{
			position = Liste_courant(libertes);

			if(!Chaine_appartient(territoire, position)) //Si une libert� n'est pas dans le territoire dit Seki, il n'y a pas Seki.
				status = 0;

		} while(Liste_suivant(libertes) && !status);

		Libertes_vider(libertes);
		Liste_detruire(libertes);

		Chaine_vider(chaine);
		Chaine_detruire(chaine);

		Liste_supprimerCourant(chaines);

	} while(!Liste_estVide(chaines)); // On s'arr�te pas quand status=0 car il faut d�sallouer toutes les choses !

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

