#include <stdlib.h>

#include "include/Territoire.h"
#include "include/Plateau.h"
#include "include/Chaine.h"
#include "include/Position.h"
#include "include/Pile.h"
#include "include/Pion.h"
#include "include/Couleur.h"

Territoire determineTerritoire(Plateau plateau, Position origine)
{
	Territoire territoire;
	Pile pile;
	Position position, positionNouvelle;
	int taille, x, y;

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
			if(Plateau_get(plateau, position) == VIDE && !Chaine_appartient(territoire, position))
			{
				positionNouvelle = Position_creer(x, y);
				Chaine_inserer(territoire, positionNouvelle);
				Pile_empiler(pile, positionNouvelle);
			}
		}

		// Cas 2, à droite
		y++;
		x++;
		if(x < taille)
		{
			if(Plateau_get(plateau, position) == VIDE && !Chaine_appartient(territoire, position))
			{
				positionNouvelle = Position_creer(x, y);
				Chaine_inserer(territoire, positionNouvelle);
				Pile_empiler(pile, positionNouvelle);
			}
		}

		// Cas 3, en bas
		y++;
		x--;
		if(y < taille)
		{
			if(Plateau_get(plateau, position) == VIDE && !Chaine_appartient(territoire, position))
			{
				positionNouvelle = Position_creer(x, y);
				Chaine_inserer(territoire, positionNouvelle);
				Pile_empiler(pile, positionNouvelle);
			}
		}

		// Cas 4, à gauche
		y--;
		x--;
		if(x >= 0)
		{
			if(Plateau_get(plateau, position) == VIDE && !Chaine_appartient(territoire, position))
			{
				positionNouvelle = Position_creer(x, y);
				Chaine_inserer(territoire, positionNouvelle);
				Pile_empiler(pile, positionNouvelle);
			}
		}

	}

	return territoire;
}

