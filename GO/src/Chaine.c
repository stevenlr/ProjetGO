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
