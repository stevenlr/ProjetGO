/**
 * @brief Fonctions concernant le Pion
 * @file Pion.c
 */

#include <stdlib.h>
#include <assert.h>

#include "include/Pion.h"
#include "include/Couleur.h"
#include "include/Position.h"

/**
 * Pion
 */
struct Pion {
	Position position;	/**< Position du pion	*/
	Couleur couleur; 	/**< Couleur du pion	*/
};

Pion Pion_creer(Position position, Couleur couleur)
{
	Pion pion;

	pion = (Pion) malloc(sizeof(struct Pion));

	if(pion == NULL)
		return NULL;

	pion->position = position;
	pion->couleur = couleur;

	return pion;
}

void Pion_detruire(Pion pion)
{
	assert(pion);

	free(pion);
}

Couleur Pion_getCouleur(Pion pion)
{
	assert(pion);

	return pion->couleur;
}

Position Pion_getPosition(Pion pion)
{
	assert(pion);

	return pion->position;
}

int Pion_estIdentique(Pion pion1, Pion pion2)
{
	return pion1->couleur == pion2->couleur
			&& Position_estIdentique(Pion_getPosition(pion1), Pion_getPosition(pion2));
}
