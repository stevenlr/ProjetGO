/**
 * @file Pile.h
 */

#ifndef PILE_H_
#define PILE_H_

#include "Liste.h"

typedef Liste Pile;

/**
 * Cr�e une pile
 *
 * @return pile
 */
Pile Pile_creer();

/**
 * D�truit une pile
 *
 * @param Pointeur sur pile
 */
void Pile_detruire(Pile pile);

/**
 * V�rifie si la pile est vide
 *
 * @param pile
 * @return 1 si vide, sinon 0
 */
int Pile_estVide(Pile pile);

/**
 * D�pile un �l�ment de la pile
 *
 * @param pile
 * @return Pointeur sur l'�l�ment d�pil�
 */
void* Pile_depiler(Pile pile);

/**
 * Empile un �l�ment
 *
 * @param pile
 * @param ptr Pointeur sur un �l�ment
 */
void Pile_empiler(Pile pile, void* ptr);

#endif
