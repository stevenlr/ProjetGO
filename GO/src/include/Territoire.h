/**
 * @file Territoire.h
 * @brief 
 */

#ifndef TERRITOIRE_H_
#define TERRITOIRE_H_

#include "Chaine.h"
#include "Plateau.h"
#include "Position.h"

typedef Chaine Territoire;

/**
 * Determine le territoire de la case origine
 * @param plateau
 * @param pos
 * @return territoire : Chaine des cases du territoires
 */
Territoire determineTerritoire(Plateau plateau,Position origine);

#endif
