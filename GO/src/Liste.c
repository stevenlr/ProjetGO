/**
 * @file Liste.c
 * @brief Liste doublement chaînée.
 */

#include <stdlib.h>
#include <assert.h>

#include "include/Liste.h"

/**
 * Un élément de la liste double chaînée.
 */
struct _ElementListe {
	struct _ElementListe* precedent;	/**< Pointeur vers l'élément suivant dans la liste. */
	struct _ElementListe* suivant;		/**< Pointeur vers l'élément précédent dans la liste. */
	void* ptr;							/**< Objet stocké. */
};

typedef struct _ElementListe ElementListe;

/**
 * Ramasse miettes, car des ElementListe sont sans arrêt allouées et désallouées.
 */
static ElementListe* gc[100];
static int gcIndex = 0;

void Liste_initGC()
{
	int i;

	for(i = 0; i < 100; i++)
		gc[i] = NULL;
}

void Liste_nettoyerGC()
{
	int i = 0;

	for(i = gcIndex - 1; i >= 0; i--)
	{
		free(gc[i]);
		gc[i] = NULL;
	}

	gcIndex = 0;
}

static ElementListe* Liste_gcAllouer()
{
	ElementListe* element;

	if(gcIndex == 0)
	{
		return (ElementListe*) malloc(sizeof(ElementListe));
	}

	element = gc[--gcIndex];
	gc[gcIndex] = NULL;

	return element;
}

static void Liste_gcDesallouer(ElementListe* element)
{
	if(gcIndex == 100)
	{
		free(element);
		return;
	}

	gc[gcIndex++] = element;
}

// Fin du ramasse miettes.

/**
 * Liste doublement chaînée.
 */
struct Liste {
	ElementListe* tete;		/**< Pointeur vers le début de la liste. */
	ElementListe* queue;	/**< Pointeur vers la fin de la liste. */
	ElementListe* courant;	/**< Pointeur vers l'élément courant. */
	int nbElements;
};

/**
 * Crée un élément de liste.
 *
 * @return L'élément créé. NULL en cas d'erreur.
 */
static ElementListe* ElementListe_creer(void* ptr);

/**
 * Détruit un élément de liste.
 *
 * @param element L'élément à détruire.
 */
static void ElementListe_detruire(ElementListe* element);

// Fonctions privées ==========================================================

static ElementListe* ElementListe_creer(void* ptr)
{
	ElementListe* element = NULL;

	element = Liste_gcAllouer();

	if(element == NULL)
		return NULL;

	element->precedent = NULL;
	element->suivant = NULL;
	element->ptr = ptr;

	return element;
}

static void ElementListe_detruire(ElementListe* element)
{
	assert(element != NULL);

	element->precedent = NULL;
	element->suivant = NULL;
	element->ptr = NULL;

	Liste_gcDesallouer(element);
}

// Fonctions publiques ========================================================

Liste Liste_creer()
{
	Liste liste = NULL;

	liste = (Liste) malloc(sizeof(struct Liste));

	if(liste == NULL)
		return NULL;

	liste->courant = NULL;
	liste->tete = NULL;
	liste->queue = NULL;
	liste->nbElements = 0;

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
	liste->courant = liste->tete;
}

void Liste_queue(Liste liste)
{
	assert(liste != NULL);
	liste->courant = liste->queue;
}

int Liste_estVide(Liste liste)
{
	assert(liste != NULL);
	return liste->nbElements == 0;
}

void* Liste_courant(Liste liste)
{
	assert(liste != NULL);

	if(liste->courant == NULL)
		return NULL;
	
	return liste->courant->ptr;
}

int Liste_suivant(Liste liste)
{
	assert(liste);

	if(liste->courant == NULL)
		return 0;
	
	if(liste->courant->suivant == NULL)
		return 0;
	
	liste->courant = liste->courant->suivant;

	return 1;
}

int Liste_precedent(Liste liste)
{
	assert(liste);

	if(liste->courant == NULL)
		return 0;
	
	if(liste->courant->precedent == NULL)
		return 0;
	
	liste->courant = liste->courant->precedent;

	return 1;
}

void Liste_insererCourant(Liste liste, void* ptr)
{
	ElementListe* element;

	element = ElementListe_creer(ptr);

	if(liste->courant == NULL)
	{
		liste->tete = element;
		liste->queue = element;
		liste->courant = element;
		liste->nbElements++;

		return;
	}

	element->suivant = liste->courant->suivant;
	element->precedent = liste->courant;
	liste->courant->suivant = element;

	if(element->suivant != NULL)
		element->suivant->precedent = element;

	if(liste->queue == liste->courant)
		liste->queue = element;
	
	liste->courant = element;
	liste->nbElements++;
}

void Liste_insererTete(Liste liste, void* ptr)
{
	ElementListe* element;

	element = ElementListe_creer(ptr);

	if(liste->tete == NULL)
	{
		liste->tete = element;
		liste->queue = element;
		liste->courant = element;
		liste->nbElements++;

		return;
	}

	element->suivant = liste->tete;
	liste->tete->precedent = element;
	liste->tete = element;
	liste->courant = element;
	liste->nbElements++;
}

void Liste_insererQueue(Liste liste, void* ptr)
{
	Liste_queue(liste);
	Liste_insererCourant(liste, ptr);
}

void Liste_supprimerCourant(Liste liste)
{
	ElementListe* element;

	element = liste->courant;

	if(element == NULL)
		return;
	
	if(element->precedent != NULL)
		element->precedent->suivant = element->suivant;
	
	if(element->suivant != NULL)
		element->suivant->precedent = element->precedent;
	
	if(liste->tete == element)
		liste->tete = element->suivant;
	
	if(liste->queue == element)
		liste->queue = element->precedent;
	
	if(element->suivant != NULL)
		liste->courant = element->suivant;
	else
		liste->courant = element->precedent;

	liste->nbElements--;
}

int Liste_getNbElements(Liste liste)
{
	assert(liste);

	return liste->nbElements;
}

void Liste_setCourant(Liste liste, int i)
{
	assert(liste);
	assert(i >= 0 && i < liste->nbElements);

	Liste_tete(liste);

	while(i > 0)
	{
		Liste_suivant(liste);
		i--;
	}
}
