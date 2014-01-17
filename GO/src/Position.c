/**
 * @brief Fonctions concernant une position
 * @file Position.c
 */

#include <stdlib.h>
#include <assert.h>

#include "include/Couleur.h"
#include "include/Position.h"


/**
 * Position
 */
struct Position{
	int x;	/**< Abscisse */
	int y;	/**< Ordonnée */
};

/**
 * Ramasse miettes, car des positions sont sans arrêt allouées et désallouées.
 */
static Position gc[100];
static int gcIndex = 0;

void Position_initGC()
{
	int i;

	for(i = 0; i < 100; i++)
		gc[i] = NULL;
}

void Position_nettoyerGC()
{
	int i = 0;

	for(i = gcIndex - 1; i >= 0; i--)
	{
		free(gc[i]);
		gc[i] = NULL;
	}

	gcIndex = 0;
}

static Position Position_gcAllouer()
{
	Position position;

	if(gcIndex == 0)
	{
		return (Position) malloc(sizeof(struct Position));
	}

	position = gc[--gcIndex];
	gc[gcIndex] = NULL;

	return position;
}

static void Position_gcDesallouer(Position position)
{
	if(gcIndex == 100)
	{
		free(position);
		return;
	}

	gc[gcIndex++] = position;
}

// Fin du ramasse miettes.

Position Position_creer(int x, int y)
{
	Position position;

	position = Position_gcAllouer();

	if(position == NULL)
		return NULL;

	position->x = x;
	position->y = y;

	return position;
}

Position Position_copier(Position position)
{
	assert(position);

	return Position_creer(position->x, position->y);
}

void Position_detruire(Position position)
{
	assert(position);

	Position_gcDesallouer(position);
}

int Position_getX(Position position)
{
	assert(position);

	return position->x;
}

int Position_getY(Position position)
{
	assert(position);

	return position->y;
}

void Position_setX(Position position, int x)
{
	assert(position);

	position->x = x;
}

void Position_setY(Position position, int y)
{
	assert(position);

	position->y = y;
}

int Position_estIdentique(Position position1, Position position2)
{
	return position1->x == position2->x
			&& position1->y == position2->y;
}
