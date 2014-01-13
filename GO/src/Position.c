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

	position = (Position) malloc(sizeof(Position));

	if(position == NULL)
		return NULL;

	position->x = x;
	position->y = y;

	return position;
}

void Position_detruire(Position position)
{
	assert(position);

	free(position);
}

Couleur Position_getX(Position position)
{
	assert(position);

	return position->x;
}

Position Position_getY(Position position)
{
	assert(position);

	return position->y;
}

int Position_estIdentique(Position position1, Position position2)
{
	return position1->x == position2->x
			&& position1->y == position2->y;
}
