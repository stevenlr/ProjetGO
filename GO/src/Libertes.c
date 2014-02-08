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
	int taille, x, y, i, ox, oy;
	int decalages[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	if((libertes = Liste_creer()) == NULL)
		return NULL;

	taille = Plateau_getTaille(plateau);
	Chaine_tete(chaine);

	position = Position_creer(0, 0);

	do
	{
		ox = Position_getX(Chaine_courant(chaine));
		oy = Position_getY(Chaine_courant(chaine));

		for(i = 0; i < 4; i++)
		{
			x = ox + decalages[i][0];
			y = oy + decalages[i][1];

			Position_setX(position, x);
			Position_setY(position, y);

			if(x < 0 || y < 0 || x >= taille || y >= taille)
				continue;

			if(Plateau_get(plateau, position) == VIDE && !(Libertes_appartient(libertes, position)))
				Liste_insererQueue(libertes, Position_copier(position));
		}

	} while(Chaine_suivant(chaine));

	Position_detruire(position);

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

void Libertes_vider(Libertes libertes)
{
	assert(libertes);

	if(Liste_estVide(libertes))
		return;

	Liste_tete(libertes);

	do
	{
		Position_detruire(Liste_courant(libertes));
		Liste_supprimerCourant(libertes);
	} while(!Liste_estVide(libertes));
}
