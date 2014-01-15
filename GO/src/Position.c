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

Position Position_creer(int x, int y)
{
	Position position;

	position = (Position) malloc(sizeof(struct Position));

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

	free(position);
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
