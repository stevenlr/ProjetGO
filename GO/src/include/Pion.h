/**
 * @file Pion.h
 * @brief 
 */

#ifndef PION_H_
#define PION_H_

#include "Couleur.h"
#include "Position.h"

typedef struct {
	Position position;	/**< Position du pion	*/
	Couleur couleur; 	/**< Couleur du pion	*/
} Pion;

/**
 * Vérifie si deux Pions sont identiques.
 *
 * @param pion1
 * @param pion2
 * @return 1 si identique, sinon 0
 */
int Pion_estIdentique(Pion pion1, Pion pion2);

/**
 * Creer un pion
 *
 * @param position
 * @param couleur
 * @return Pointeur sur le Pion créé
 */
Pion* Pion_creer(Position position, Couleur couleur);
#endif
