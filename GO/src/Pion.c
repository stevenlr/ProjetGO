/**
 * @brief Fonctions concernant le Pion
 * @file Pion.c
 */

#include "include/Pion.h"

int Pion_estIdentique(Pion pion1, Pion pion2)
{
	return pion1.couleur == pion2.couleur
			&& pion1.position.x == pion2.position.x
			&& pion1.position.y == pion2.position.y;
}
