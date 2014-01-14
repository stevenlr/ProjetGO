#include <stdlib.h>

#include "include/Territoire.h"
#include "include/Plateau.h"
#include "include/Chaine.h"
#include "include/Position.h"
#include "include/Pile.h"
#include "include/Pion.h"
#include "include/Couleur.h"

/*=FONCTION PRIVEE=======================================================*/

static void Territoire_determinerCouleur(Couleur couleur, Territoire territoire, int estNeutre)
{
	if(!estNeutre && couleur != VIDE)
	{
		if(Chaine_getCouleur(territoire) == VIDE)
		{
			Chaine_setCouleur(territoire, couleur);
		}
		else
		{
			Chaine_setCouleur(territoire, VIDE);
			estNeutre++;
		}
	}
}

/*=FONCTIONS PUBLIQUES===================================================*/

Territoire determineTerritoire(Plateau plateau, Position origine)
{
	Territoire territoire;
	Pile pile;
	Position position, positionNouvelle;
	int taille, x, y, estNeutre = 0;

	if((pile = Pile_creer()) == NULL)
		return NULL;

	if((territoire = Chaine_creer()) == NULL)
		return NULL;

	position = Position_copier(origine);

	Matrice_getTaille(plateau, NULL, &taille);

	if(Plateau_get(plateau, origine) != VIDE)
		return NULL;

	Chaine_inserer(territoire, position);
	Pile_empiler(pile, position);

	while((position = Pile_depiler(pile)) != NULL)
	{
		x = Position_getX(position);
		y = Position_getY(position);

		// Cas 1, en haut
		y--;
		if(y >= 0)
		{
			positionNouvelle = Position_creer(x, y);

			if(Plateau_get(plateau, positionNouvelle) == VIDE && !Chaine_appartient(territoire, positionNouvelle))
			{
				Chaine_inserer(territoire, positionNouvelle);
				Pile_empiler(pile, positionNouvelle);
			}
			else
				free(positionNouvelle);

			Territoire_determinerCouleur(Plateau_get(plateau, positionNouvelle), territoire, estNeutre);
		}

		// Cas 2, à droite
		y++;
		x++;
		if(x < taille)
		{
			positionNouvelle = Position_creer(x, y);

			if(Plateau_get(plateau, positionNouvelle) == VIDE && !Chaine_appartient(territoire, positionNouvelle))
			{
				Chaine_inserer(territoire, positionNouvelle);
				Pile_empiler(pile, positionNouvelle);
			}
			else
				free(positionNouvelle);

			Territoire_determinerCouleur(Plateau_get(plateau, positionNouvelle), territoire, estNeutre);
		}

		// Cas 3, en bas
		y++;
		x--;
		if(y < taille)
		{
			positionNouvelle = Position_creer(x, y);

			if(Plateau_get(plateau, positionNouvelle) == VIDE && !Chaine_appartient(territoire, positionNouvelle))
			{
				Chaine_inserer(territoire, positionNouvelle);
				Pile_empiler(pile, positionNouvelle);
			}
			else
				free(positionNouvelle);

			Territoire_determinerCouleur(Plateau_get(plateau, positionNouvelle), territoire, estNeutre);
		}

		// Cas 4, à gauche
		y--;
		x--;
		if(x >= 0)
		{
			positionNouvelle = Position_creer(x, y);

			if(Plateau_get(plateau, positionNouvelle) == VIDE && !Chaine_appartient(territoire, positionNouvelle))
			{
				Chaine_inserer(territoire, positionNouvelle);
				Pile_empiler(pile, positionNouvelle);
			}
			else
				free(positionNouvelle);

			Territoire_determinerCouleur(Plateau_get(plateau, positionNouvelle), territoire, estNeutre);
		}

	}

	return territoire;
}

