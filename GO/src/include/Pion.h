/**
 * @file Pion.h
 * @brief Pions de jeu de Go.
 */

#ifndef PION_H_
#define PION_H_

#include "Couleur.h"
#include "Position.h"

typedef struct Pion* Pion;

/**
 * Creer un pion
 *
 * @param position
 * @param couleur
 * @return Pointeur sur le Pion créé
 */
Pion Pion_creer(Position position, Couleur couleur);

/**
 * Détruit un pion.
 *
 * @param pion
 */
void Pion_detruire(Pion pion);

/**
 * Retourne la position du pion.
 *
 * @param pion
 * @return Position du pion.
 */
Position Pion_getPosition(Pion pion);

/**
 * Retourne la couleur du pion.
 *
 * @param pion
 * @return Couleur du pion.
 */
Couleur Pion_getCouleur(Pion pion);

/**
 * Vérifie si deux Pions sont identiques.
 *
 * @param pion1
 * @param pion2
 * @return 1 si identique, sinon 0
 */
int Pion_estIdentique(Pion pion1, Pion pion2);

#endif
