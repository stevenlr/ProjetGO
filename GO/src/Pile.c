/**
 * Pile.c
 *
 *  @date 10 janv. 2014
 *  @author Gautier
 */

#include <stdlib.h>
#include <assert.h>
#include "include/Pile.h"


Pile Pile_creer()
{
	return Liste_creer();
}

void Pile_detruire(Pile* pile)
{
	Liste_detruire(*pile);

	pile = NULL;
}

int Pile_estVide(Pile pile)
{
	return Liste_estVide(pile);	//assert(pile) est fait dans cette fonction
}

void* Pile_depiler(Pile pile)
{
	void* ptr;

	if( Pile_estVide(pile) )	//assert(pile) est fait dans cette fonction
		return NULL;

	Liste_queue(pile);

	ptr = Liste_courant(pile);

	Liste_supprimerCourant(pile);

	return ptr;
}

void Pile_empiler(Pile pile, void* ptr)
{
	assert(pile);

	Liste_insererQueue(pile, ptr);
}

