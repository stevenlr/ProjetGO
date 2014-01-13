/**
 * @file Chaine.c
 * @brief
 * @date 9 janv. 2014
 * @author Gautier
 **/

#include <stdlib.h>
#include <assert.h>

#include "include/Liste.h"
#include "include/Couleur.h"
#include "include/Chaine.h"

/**
 * Chaine.
 */
struct Chaine {
	Liste liste;		/**< Liste de position. */
	Couleur couleur;	/**< Couleur de la chaine. */
};

Chaine Chaine_creer()
{
	Chaine chaine;

	chaine = (Chaine) malloc(sizeof(Chaine));
	if(chaine == NULL)
		return NULL;

	if((chaine->liste = Liste_creer()) == NULL)
	{
		free(chaine);
		return NULL;
	}

	chaine->couleur = VIDE;

	return chaine;
}

void Chaine_detruire(Chaine chaine)
{
	assert(chaine);

	Liste_detruire(chaine->liste);
	free(chaine);
}

void Chaine_vider(Chaine chaine)
{
	Position pos;

	assert(chaine);

	assert(chaine);

	if(Chaine_estVide(chaine))
		return 0;

	Chaine_tete(chaine);

	do
	{
		pos = Chaine_courant(chaine);
		assert(pos);
		free(pos);

		Liste_supprimerCourant(chaine->liste);
	} while(!Chaine_estVide(chaine));
}

int Chaine_appartient(Chaine chaine, Position position)
{
	Position positionCourant;

	assert(chaine);

	if(Chaine_estVide(chaine))
		return 0;

	Chaine_tete(chaine);

	do
	{
		positionCourant = Chaine_courant(chaine);

		if(Position_estIdentique(positionCourant, position))
			return 1;

	} while(Chaine_suivant(chaine));

	return 0;
}

int Chaine_estVide(Chaine chaine)
{
	assert(chaine);

	return Liste_estVide(chaine->liste);
}

Position Chaine_courant(Chaine chaine)
{
	assert(chaine);

	return Liste_courant(chaine->liste);
}

int Chaine_suivant(Chaine chaine)
{
	assert(chaine);

	return Liste_suivant(chaine->liste);
}

void Chaine_tete(Chaine chaine)
{
	assert(chaine);

	Liste_tete(chaine->liste);
}

void Chaine_inserer(Chaine chaine, Position position)
{
	assert(chaine);

	Liste_insererQueue(chaine->liste, position);
}
