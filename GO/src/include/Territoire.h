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
 *
 * @param plateau
 * @param pos
 * @return territoire : Chaine des cases du territoires. La couleur du territoire est VIDE si territoire neutre.
 */
Territoire Territoire_determinerTerritoire(Plateau plateau,Position origine);

/**
 * Déterminer les chaines entourants le territoire.
 *
 * @param territoire
 * @return Chaines
 */
Chaines Territoire_determinerChainesAutour(Territoire territoire, Plateau plateau);

/**
 * Détermine si un territoire forme un seki pour les chaines concernées.
 *
 * @param territoire
 * @param plateau
 * @return 1 si vrai, sinon 0.
 */
int Territoire_estUnSeki(Territoire territoire,  Plateau plateau);

/**
 * Determiner le nombre de cases d'un territoire
 *
 * @param territoire
 * @return nombre de cases du territoire
 */
int Territoire_determinerNbCases(Territoire territoire);

#endif
