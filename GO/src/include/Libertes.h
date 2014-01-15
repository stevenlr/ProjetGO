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
 * Pour des soucis de simplicit�, les libert�s seront stock�es comme des listes
 * de pions et non de position. La couleur ne sera donc pas prise en compte.
 */
typedef Liste Libertes;

/**
 * D�termine l'ensemble des libert�s d'une chaine donn�e en fonction
 * de la position des pions sur le plateau
 *
 * @param plateau
 * @param chaine Chaine pour laquelle d�terminer les libert�s.
 * @return Liste des libert�s de la chaine
 */
Libertes Libertes_determinerLibertes(Plateau plateau, Chaine chaine);

/**
 * V�rifie l'appartenance d'une position � une liste de libertes.
 *
 * @param libertes
 * @param position
 * @return 1 si la position appartient � la liste, 0 sinon.
 */
int Libertes_appartient(Libertes libertes, Position position);

/**
 * Vide la liste des libert�s et d�salloue ses �l�ments.
 *
 * @param libertes
 */
void Libertes_vider(Libertes libertes);

#endif
