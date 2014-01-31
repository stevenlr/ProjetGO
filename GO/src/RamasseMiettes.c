/**
 * @file RamasseMiettes.c
 * @brief 
 */

#include <stdlib.h>
#include <assert.h>

#include "include/RamasseMiettes.h"

struct RamasseMiettes {
	int nbElementsMax;
	int nbElements;
	int tailleElement;
	void** elements;
};

RamasseMiettes RamasseMiettes_creer(int nbElements, int tailleElement)
{
	RamasseMiettes gc;
	int i;

	gc = malloc(sizeof(struct RamasseMiettes));

	if(gc == NULL)
		return NULL;

	gc->nbElementsMax = nbElements;
	gc->nbElements = 0;
	gc->tailleElement = tailleElement;

	gc->elements = malloc(sizeof(void*) * nbElements);

	if(gc->elements == NULL)
	{
		free(gc);
		return NULL;
	}

	return gc;
}

void RamasseMiettes_detruire(RamasseMiettes gc)
{
	assert(gc);

	free(gc->elements);
	free(gc);
}

void* RamasseMiettes_allouer(RamasseMiettes gc)
{
	assert(gc);

	if(gc->nbElements == 0)
		return malloc(gc->tailleElement);

	return gc->elements[--(gc->nbElements)];
}

void RamasseMiettes_desallouer(RamasseMiettes gc, void* ptr)
{
	assert(gc);
	assert(ptr);

	if(gc->nbElements == gc->nbElementsMax)
	{
		free(ptr);
		return;
	}

	gc->elements[(gc->nbElements)++] = ptr;
}

void RamasseMiettes_vider(RamasseMiettes gc)
{
	int i;

	assert(gc);

	for(i = 0; i < gc->nbElements; i++)
	{
		free(gc->elements[i]);
	}

	gc->nbElements = 0;
}
