/**
 * @file Chaine.c
 * @brief
 * @date 9 janv. 2014
 * @author Gautier
 **/

#include <stdlib.h>
#include <assert.h>

#include "include/Liste.h"
#include "include/Pion.h"
#include "include/Chaine.h"

Chaine Chaine_creer()
{
	return Liste_creer();
}

void Chaine_detruire(Chaine chaine)
{
	assert(chaine);

	Liste_detruire(chaine);
}

void Chaine_tete(Chaine chaine)
{
	Liste_tete(chaine);
}

int Chaine_suivant(Chaine chaine)
{
	return Liste_suivant(chaine);
}

Pion Chaine_courant(Chaine chaine)
{
	return Liste_courant(chaine);
}

void Chaine_inserer(Chaine chaine, Pion pion)
{
	Liste_insererCourant(chaine, pion);
}

int Chaine_appartient(Chaine chaine, Pion pion)
{
	Pion pionCourant;

	assert(chaine);

	if(Liste_estVide(chaine))
		return 0;

	Liste_tete(chaine);

	do
	{
		pionCourant = Liste_courant(chaine);

		if(Pion_estIdentique(pionCourant, pion))
			return 1;

	} while(Liste_suivant(chaine));

	return 0;
}

int Chaine_estVide(Chaine chaine)
{
	return Liste_estVide(chaine);
}

