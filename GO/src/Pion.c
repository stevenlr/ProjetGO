/**
 * @brief Fonctions concernant le Pion
 * @file Pion.c
 */

#include "include/Pion.h"
#include "include/Couleur.h"
#include "include/Position.h"

int Pion_estIdentique(Pion pion1, Pion pion2)
{
	return pion1.couleur == pion2.couleur
			&& pion1.position.x == pion2.position.x
			&& pion1.position.y == pion2.position.y;
}

Pion* Pion_creer(Position position, Couleur couleur)
{
	Pion pion;
	pion.position = position;
	pion.couleur = couleur;

	return &pion;
}
