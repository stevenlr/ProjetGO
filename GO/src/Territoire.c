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

Chaines Territoire_determinerChainesAutour(Territoire territoire, Plateau plateau)
{
	Chaines chaines;
	Chaine chaine;
	Position position;
	int x, y, taille;

	if(Chaine_estVide(territoire))
		return NULL;

	chaines = Liste_creer();

	Matrice_getTaille(plateau, NULL, &taille);

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

	}while(Chaine_suivant(territoire));

	return chaines;
}

int Territoire_estUnSeki(Territoire territoire,  Plateau plateau)
{
	Chaines chaines;
	Chaine chaine;
	Libertes libertes;
	Position position;

	chaines = Territoire_determinerChainesAutour(territoire, plateau);

	do
	{
		chaine = Liste_courant(chaines);
		libertes = Libertes_determinerLibertes(plateau, chaine);	//Forcément, il y a des libertés vu que ce sont les chaines qui entourent un territoire vide.

		do
		{
			position = Liste_courant(libertes);

			if(!Chaine_appartient(territoire, position))	//Si une liberté n'est pas dans le territoire dit Seki, il n'y a pas Seki.
				return 0;

		}while(Liste_suivant(libertes));

	}while(Liste_suivant(chaines));

	return 1;
}

