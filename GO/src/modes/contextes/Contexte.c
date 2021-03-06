/**
 * @file Contexte.c
 */

#include <stdlib.h>
#include <assert.h>

#include "include/modes/contextes/Contexte.h"
#include "include/modes/contextes/ContexteGraphique.h"
#include "include/modes/contextes/ContexteConsole.h"

static TypeContexte idContexteCourant;
static Contexte contexteCourant = NULL;

int Contexte_initialiser(TypeContexte type)
{
	if(contexteCourant != NULL)
		return 0;

	idContexteCourant = type;

	switch(idContexteCourant)
	{
		case GRAPHIQUE:
			contexteCourant = ContexteGraphique_creer();
			break;
		case CONSOLE:
			contexteCourant = ContexteConsole_creer();
			break;
		default:
			break;
	}

	if(contexteCourant == NULL)
		return 0;

	return 1;
}

void Contexte_detruire()
{
	assert(contexteCourant);

	switch(idContexteCourant)
	{
		case GRAPHIQUE:
			ContexteGraphique_detruire(contexteCourant);
			break;
		case CONSOLE:
			ContexteConsole_detruire(contexteCourant);
			break;
		default:
			break;
	}

	contexteCourant = NULL;
}

Contexte Contexte_get()
{
	return contexteCourant;
}

TypeContexte Contexte_getID()
{
	return idContexteCourant;
}
