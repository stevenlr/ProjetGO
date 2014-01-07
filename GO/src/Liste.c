/**
 * @file Liste.c
 * @brief Liste doublement cha�n�e.
 */

#include <stdlib.h>
#include <assert.h>

#include "include/Liste.h"

/**
 * Un �l�ment de la liste double cha�n�e.
 */
struct _ElementListe {
	struct _ElementListe* precedent;	/**< Pointeur vers l'�l�ment suivant dans la liste. */
	struct _ElementListe* suivant;		/**< Pointeur vers l'�l�ment pr�c�dent dans la liste. */
	void* ptr;							/**< Objet stock�. */
};

typedef struct _ElementListe ElementListe;

/**
 * Liste doublement cha�n�e.
 */
struct Liste {
	ElementListe* tete;		/**< Pointeur vers le d�but de la liste. */
	ElementListe* queue;	/**< Pointeur vers la fin de la liste. */
	ElementListe* courant;	/**< Pointeur vers l'�l�ment courant. */
};

/**
 * Cr�� un �l�ment de liste.
 * On ne devrait pas avoir � s'en servir en dehors des fonctions de Liste.
 *
 * @return L'�l�ment cr��. NULL en cas d'erreur.
 */
ElementListe* ElementListe_creer();

/**
 * D�truit un �l�ment de liste.
 * On ne devrait pas avoir � s'en servir en dehors des fonctions de Liste.
 *
 * @param element L'�l�ment � d�truire.
 */
void ElementListe_detruire(ElementListe* element);

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

Liste Liste_creer()
{
	Liste liste = NULL;

	liste = (Liste) malloc(sizeof(Liste));

	if(liste == NULL)
		return NULL;

	liste->courant = NULL;
	liste->tete = NULL;
	liste->queue = NULL;

	return liste;
}

void Liste_detruire(Liste liste)
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

void Liste_tete(Liste liste)
{
	assert(liste != NULL);
	liste->courant = liste->queue;
}

void Liste_queue(Liste liste)
{
	assert(liste != NULL);
	liste->courant = liste->queue;
}

int Liste_estVide(Liste liste)
{
	assert(liste != NULL);
	return liste->tete == NULL;
}
