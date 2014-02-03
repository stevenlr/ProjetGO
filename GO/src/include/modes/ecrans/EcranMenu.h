/**
 * @file EcranMenu.h
 * @brief Ecran de menu principal.
 */

#ifndef ECRANMENU_H_
#define ECRANMENU_H_

#include "Ecran.h"

/**
 * Initialise le menu principal.
 */
void EcranMenu_init();

/**
 * D�truit les �tats du menu principal.
 */
void EcranMenu_detruire();

/**
 * Logique de l'�cran de menu.
 */
void EcranMenu_main();

/**
 * Retourne la fonction d'entr�es de menu.
 * @return
 */
FonctionEntreeEcran EcranMenu_getEntreeFct();

/**
 * Retourne la fonction de sortie de menu.
 * @return
 */
FonctionSortieEcran EcranMenu_getSortieFct();

/**
 * Ev�nement : Quitte le jeu.
 */
void EcranMenu_eventQuitter();

/**
 * Ev�nement : Reprendre la derni�re partie, dont aller � l'�cran de jeu.
 */
void EcranMenu_eventReprendre();

/**
 * Ev�nement : Cr�e une nouvelle partie, donc aller � l'�cran d'options.
 */
void EcranMenu_eventNouvellePartie();

/**
 * Ev�nement : Ouvre le tutoriel.
 */
void EcranMenu_eventGuide();

#endif
