/**
 * @file Chaine.h
 * @brief 
 */

#ifndef CHAINE_H_
#define CHAINE_H_

#include "Liste.h"
#include "Pion.h"

typedef Liste Chaine;

/**
 * Verifie si un pion appartient à la chaine
 * @param chaine
 * @param pion
 * @return 1 si le pion est dans la chaine, sinon 0
 */
int Chaine_appartient(Chaine chaine, Pion pion);

#endif
