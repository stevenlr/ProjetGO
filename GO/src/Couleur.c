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
		case AURABLANC:
			return 'o';
		case AURANOIR:
			return 'x';
		default:
			return ' ';
	}
}

Couleur Couleur_charVersCouleur(char c)
{
	switch(c)
	{
		case '.':
			return VIDE;
		case 'O':
			return BLANC;
		case 'X':
			return NOIR;
		case 'o':
			return AURABLANC;
		case 'x':
			return AURANOIR;
		default:
			return AURAVIDE;
	}
}


