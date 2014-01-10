/**
 * @file Pile.h
 */

#ifndef PILE_H_
#define PILE_H_

#include "Liste.h"

typedef Liste Pile;

/**
 * Crée une pile
 *
 * @return pile
 */
Pile Pile_creer();

/**
 * Détruit une pile
 *
 * @param Pointeur sur pile
 */
void Pile_detruire(Pile pile);

/**
 * Vérifie si la pile est vide
 *
 * @param pile
 * @return 1 si vide, sinon 0
 */
int Pile_estVide(Pile pile);

/**
 * Dépile un élément de la pile
 *
 * @param pile
 * @return Pointeur sur l'élément dépilé
 */
void* Pile_depiler(Pile pile);

/**
 * Empile un élément
 *
 * @param pile
 * @param ptr Pointeur sur un élément
 */
void Pile_empiler(Pile pile, void* ptr);

#endif
