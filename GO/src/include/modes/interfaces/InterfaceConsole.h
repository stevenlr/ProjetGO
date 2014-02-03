/**
 * @file InterfaceConsole.h
 * @brief Fonctions d'entrées/sorties en contexte console.
 */

#ifndef INTERFACECONSOLE_H_
#define INTERFACECONSOLE_H_

#include "include/modes/etats/EtatsJeu.h"
#include "include/modes/etats/EtatsMenu.h"
#include "include/modes/etats/EtatsGuide.h"
#include "include/modes/etats/EtatsOptions.h"

/**
 * Entrées de l'écran de jeu.
 * @param etats
 */
void InterfaceConsole_entreeJeu(EtatsJeu* etats);

/**
 * Sorties de l'écran de jeu.
 * @param etats
 */
void InterfaceConsole_sortieJeu(EtatsJeu* etats);

/**
 * Entrées de l'écran de menu.
 * @param etats
 */
void InterfaceConsole_entreeMenu(EtatsMenu* etats);

/**
 * Sorties de l'écran de menu.
 * @param etats
 */
void InterfaceConsole_sortieMenu(EtatsMenu* etats);

/**
 * Entrées de l'écran de tutoriel.
 * @param etats
 */
void InterfaceConsole_entreeGuide(EtatsGuide* etats);

/**
 * Sorties de l'écran de tutoriel.
 * @param etats
 */
void InterfaceConsole_sortieGuide(EtatsGuide* etats);

/**
 * Entrées de l'écran de création de partie.
 * @param etats
 */
void InterfaceConsole_entreeOptions(EtatsOptions* etats);

/**
 * Sorties de l'écran de création de partie.
 * @param etats
 */
void InterfaceConsole_sortieOptions(EtatsOptions* etats);

#endif
