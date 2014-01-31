/**
 * @brief Fonctions concernant une position
 * @file Position.c
 */

#include <stdlib.h>
#include <assert.h>

#include "include/RamasseMiettes.h"
#include "include/Couleur.h"
#include "include/Position.h"


/**
 * Position
 */
struct Position{
	int x;	/**< Abscisse */
	int y;	/**< Ordonn�e */
};

/**
 * Ramasse miettes, car des positions sont sans arr�t allou�es et d�sallou�es.
 */
static RamasseMiettes ramasseMiettes;

void Position_initGC()
{
	ramasseMiettes = RamasseMiettes_creer(100, sizeof(struct Position));
}

void Position_detruireGC()
{
	RamasseMiettes_vider(ramasseMiettes);
	RamasseMiettes_detruire(ramasseMiettes);
}

// Fin du ramasse miettes.

Position Position_creer(int x, int y)
{
	Position position;

	position = RamasseMiettes_allouer(ramasseMiettes);

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

	RamasseMiettes_desallouer(ramasseMiettes, position);
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
