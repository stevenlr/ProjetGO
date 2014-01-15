/**
 * @file Libertes.h
 * @brief 
 */

#ifndef LIBERTES_H_
#define LIBERTES_H_

#include "Plateau.h"
#include "Liste.h"
#include "Chaine.h"

/**
 * Pour des soucis de simplicité, les libertés seront stockées comme des listes
 * de pions et non de position. La couleur ne sera donc pas prise en compte.
 */
typedef Liste Libertes;

/**
 * Détermine l'ensemble des libertés d'une chaine donnée en fonction
 * de la position des pions sur le plateau
 *
 * @param plateau
 * @param chaine Chaine pour laquelle déterminer les libertés.
 * @return Liste des libertés de la chaine
 */
Libertes Libertes_determinerLibertes(Plateau plateau, Chaine chaine);

/**
 * Vérifie l'appartenance d'une position à une liste de libertes.
 *
 * @param libertes
 * @param position
 * @return 1 si la position appartient à la liste, 0 sinon.
 */
int Libertes_appartient(Libertes libertes, Position position);

/**
 * Vide la liste des libertés et désalloue ses éléments.
 *
 * @param libertes
 */
void Libertes_vider(Libertes libertes);

#endif
