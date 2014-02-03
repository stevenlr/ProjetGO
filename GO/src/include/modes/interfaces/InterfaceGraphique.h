/**
 * @file InterfaceGraphique.h
 * @brief Fonctions d'entr�es/sorties en contexte graphique.
 */

#ifndef INTERFACEGRAPHIQUE_H_
#define INTERFACEGRAPHIQUE_H_

#include "include/modes/etats/EtatsJeu.h"
#include "include/modes/etats/EtatsMenu.h"
#include "include/modes/etats/EtatsGuide.h"
#include "include/modes/etats/EtatsOptions.h"

/**
 * Taille d'une cellule sur le plateau.
 */
#define TAILLE_CELL 30

/**
 * Entr�es de l'�cran de jeu.
 * @param etats
 */
void InterfaceGraphique_entreeJeu(EtatsJeu* etats);

/**
 * Sorties de l'�cran de jeu.
 * @param etats
 */
void InterfaceGraphique_sortieJeu(EtatsJeu* etats);

/**
 * Entr�es de l'�cran de menu.
 * @param etats
 */
void InterfaceGraphique_entreeMenu(EtatsMenu* etats);

/**
 * Sorties de l'�cran de menu.
 * @param etats
 */
void InterfaceGraphique_sortieMenu(EtatsMenu* etats);

/**
 * Entr�es de l'�cran de tutoriel.
 * @param etats
 */
void InterfaceGraphique_entreeGuide(EtatsGuide* etats);

/**
 * Sorties de l'�cran de tutoriel.
 * @param etats
 */
void InterfaceGraphique_sortieGuide(EtatsGuide* etats);

/**
 * Entr�es de l'�cran de cr�ation de partie.
 * @param etats
 */
void InterfaceGraphique_entreeOptions(EtatsOptions* etats);

/**
 * Sorties de l'�cran de cr�ation de partie.
 * @param etats
 */
void InterfaceGraphique_sortieOptions(EtatsOptions* etats);

#endif
