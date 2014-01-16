/**
 * @file Chaines.h
 * @brief 
 */

#ifndef CHAINES_H_
#define CHAINES_H_

typedef Liste Chaines;

/**
 * Determiner si une position donnée appartient à une des chaines de la liste de chaines.
 *
 * @param chaines
 * @param position
 * @return 1 si vrai, sinon 0
 */
int Chaines_positionAppartient(Chaines chaines, Position position);

#endif
