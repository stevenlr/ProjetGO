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
 * Détruit les états du menu principal.
 */
void EcranMenu_detruire();

/**
 * Logique de l'écran de menu.
 */
void EcranMenu_main();

/**
 * Retourne la fonction d'entrées de menu.
 * @return
 */
FonctionEntreeEcran EcranMenu_getEntreeFct();

/**
 * Retourne la fonction de sortie de menu.
 * @return
 */
FonctionSortieEcran EcranMenu_getSortieFct();

/**
 * Evénement : Quitte le jeu.
 */
void EcranMenu_eventQuitter();

/**
 * Evénement : Reprendre la dernière partie, dont aller à l'écran de jeu.
 */
void EcranMenu_eventReprendre();

/**
 * Evénement : Crée une nouvelle partie, donc aller à l'écran d'options.
 */
void EcranMenu_eventNouvellePartie();

/**
 * Evénement : Ouvre le tutoriel.
 */
void EcranMenu_eventGuide();

#endif
