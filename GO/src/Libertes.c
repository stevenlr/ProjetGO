/**
 * @file Libertes.c
 * @brief
 */

#include <stdlib.h>
#include "assert.h"

#include "include/Libertes.h"
#include "include/Couleur.h"
#include "include/Pion.h"
#include "include/Liste.h"
#include "include/Position.h"
#include "include/Plateau.h"

Libertes Libertes_determinerLibertes(Plateau plateau, Chaine chaine)
{
	Libertes libertes;
	Position position;
	int taille, x, y;

	if((libertes = Liste_creer()) == NULL)
		return NULL;

	Matrice_getTaille(plateau, NULL, &taille);

	do
	{
		position = Position_copier(Liste_courant(chaine));
		x = Position_getX(position);
		y = Position_getY(position);

		// Haut
		Position_setY(position, y--);
		if(y >= 0)
		{
			if(Plateau_get(plateau, position) == VIDE && !(Libertes_appartient(libertes, position)))
				Liste_insererQueue(libertes, Position_copier(position));
		}

		// Gauche
		Position_setY(position, y++);
		Position_setX(position, x--);
		if(x >= 0)
		{
			if(Plateau_get(plateau, position) == VIDE && !(Libertes_appartient(libertes, position)))
				Liste_insererQueue(libertes, Position_copier(position));
		}

		// Bas
		Position_setY(position, y++);
		Position_setX(position, x++);
		if(y < taille)
		{
			if(Plateau_get(plateau, position) == VIDE && !(Libertes_appartient(libertes, position)))
				Liste_insererQueue(libertes, Position_copier(position));
		}

		// Droite
		Position_setY(position, y--);
		Position_setX(position, x++);
		if(x < taille)
		{
			if(Plateau_get(plateau, position) == VIDE && !(Libertes_appartient(libertes, position)))
				Liste_insererQueue(libertes, Position_copier(position));
		}

		Position_detruire(position);
	} while(Chaine_suivant(chaine));

	return libertes;
}

int Libertes_appartient(Libertes libertes, Position position)
{
	Position posCourant;

	assert(libertes);

	if(Liste_estVide(libertes))
		return 0;

	Liste_tete(libertes);

	do
	{
		posCourant = Liste_courant(libertes);

		if(Position_estIdentique(posCourant, position))
			return 1;

	} while(Liste_suivant(libertes));

	return 0;
}
