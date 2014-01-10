/**
 * @file Pile.c
 */

#include <stdlib.h>
#include <assert.h>
#include "include/Pile.h"

Pile Pile_creer()
{
	return Liste_creer();
}

void Pile_detruire(Pile pile)
{
	Liste_detruire(pile);
}

int Pile_estVide(Pile pile)
{
	return Liste_estVide(pile);
}

void* Pile_depiler(Pile pile)
{
	void* ptr;

	if(Pile_estVide(pile))
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

