/**
 * @file Libertes.h
 * @brief 
 */

#ifndef LIBERTES_H_
#define LIBERTES_H_

#include "Chaine.h"
#include "Plateau.h"

typedef Chaine Libertes;

/**
 * @brief Détermine l'ensemble des libertés d'une chaine donnée en fonction
 * de la position des pions sur le plateau
 *
 * @param plateau
 * @param chaine
 * @return libertes : Liste des libertés de la chaine
 */
Libertes determineLiberte(Plateau plateau,Chaine chaine);

#endif
