/**
 * @file Liste.c
 * @brief Liste doublement chaînée.
 */

#include <stdlib.h>
#include <assert.h>

#include "include/Liste.h"

ElementListe* ElementListe_creer()
{
	ElementListe* element = NULL;

	element = (ElementListe*) malloc(sizeof(ElementListe));

	if(element == NULL)
		return NULL;

	element->precedent = NULL;
	element->suivant = NULL;
	element->ptr = NULL;

	return element;
}

void ElementListe_detruire(ElementListe* element)
{
	assert(element != NULL);

	element->precedent = NULL;
	element->suivant = NULL;
	element->ptr = NULL;

	free(element);
}

Liste* Liste_creer()
{
	Liste* liste = NULL;

	liste = (Liste*) malloc(sizeof(Liste));

	if(liste == NULL)
		return NULL;

	liste->courant = NULL;
	liste->tete = NULL;
	liste->queue = NULL;

	return liste;
}

void Liste_detruire(Liste* liste)
{
	ElementListe *element, *suivant;

	assert(liste != NULL);
	element = liste->tete;

	while(element != NULL)
	{
		suivant = element->suivant;
		ElementListe_detruire(element);
		element = suivant;
	}

	liste->courant = NULL;
	liste->tete = NULL;
	liste->queue = NULL;

	free(liste);
}

void Liste_tete(Liste* liste)
{
	assert(liste != NULL);
	liste->courant = liste->queue;
}

void Liste_queue(Liste* liste)
{
	assert(liste != NULL);
	liste->courant = liste->queue;
}

int Liste_estVide(Liste* liste)
{
	assert(liste != NULL);
	return liste->tete == NULL;
}
