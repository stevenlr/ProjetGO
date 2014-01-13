/**
 * @file Position.h
 * @brief 
 */

#ifndef POSITION_H_
#define POSITION_H_

#include "Couleur.h"

typedef struct Position* Position;

/**
 * Creer un position
 *
 * @param position
 * @param couleur
 * @return Pointeur sur la Position créée
 */
Position Position_creer(int x, int y);

/**
 * Détruit un position.
 *
 * @param position
 */
void Position_detruire(Position position);

/**
 * Retourne la position du position.
 *
 * @param position
 * @return Position du position.
 */
Position Position_getX(Position position);

/**
 * Retourne la couleur du position.
 *
 * @param position
 * @return Couleur du position.
 */
Couleur Position_getY(Position position);

/**
 * Vérifie si deux Positions sont identiques.
 *
 * @param position1
 * @param position2
 * @return 1 si identique, sinon 0
 */
int Position_estIdentique(Position position1, Position position2);


#endif
