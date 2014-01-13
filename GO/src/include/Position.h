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
 * Copie une position.
 *
 * @param position
 * @return Position copiée.
 */
Position Position_copier(Position position);

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
int Position_getX(Position position);

/**
 * Retourne la couleur du position.
 *
 * @param position
 * @return Couleur du position.
 */
int Position_getY(Position position);

/**
 * Assigne la valeur x.
 *
 * @param position
 * @param x
 */
void Position_setX(Position position, int x);

/**
 * Assigne la valeur y.
 *
 * @param position
 * @param y
 */
void Position_setY(Position position, int y);

/**
 * Vérifie si deux Positions sont identiques.
 *
 * @param position1
 * @param position2
 * @return 1 si identique, sinon 0
 */
int Position_estIdentique(Position position1, Position position2);


#endif
