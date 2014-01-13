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
 * @brief D�termine l'ensemble des libert�s d'une chaine donn�e en fonction
 * de la position des pions sur le plateau
 *
 * @param plateau
 * @param chaine
 * @return libertes : Liste des libert�s de la chaine
 */
Libertes determineLiberte(Plateau plateau,Chaine chaine);

#endif
