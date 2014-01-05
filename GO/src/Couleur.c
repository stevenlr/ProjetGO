/**
 * @file Couleur.c
 * @brief Gestion des couleurs de pions.
 */

#include <stdlib.h>

#include "include/Couleur.h"
#include "include/Liste.h"

char Couleur_versChar(Couleur couleur)
{
	switch(couleur)
	{
		case VIDE:
			return '.';
		case BLANC:
			return 'O';
		case NOIR:
			return 'X';
		default:
			return ' ';
	}
}

