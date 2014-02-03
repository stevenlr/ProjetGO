/**
 * @file EcranOptions.h
 * @brief Ecran de création d'une partie.
 */

#ifndef ECRANOPTIONS_H_
#define ECRANOPTIONS_H_

#include "include/Couleur.h"
#include "include/Partie.h"

#include "Ecran.h"

/**
 * Initialise les états de l'écran de création de partie.
 */
void EcranOptions_init();

/**
 * Détruit les états de l'écran de création de partie.
 */
void EcranOptions_detruire();

/**
 * Logique de l'écran de création de partie.
 */
void EcranOptions_main();

/**
 * Retourne la fonction d'entrée correspondant au contexte courant pour l'écran de création de partie.
 * @return
 */
FonctionEntreeEcran EcranOptions_getEntreeFct();

/**
 * Retourne la fonction de sortie correspondant au contexte courant pour l'écran de création de partie.
 * @return
 */
FonctionSortieEcran EcranOptions_getSortieFct();

/**
 * Evénement : quitter l'écran actuel.
 * @param menu 0 : on ferme le jeu, 1 : on revient à l'écran d'accueil.
 */
void EcranOptions_eventQuitter(int menu);

/**
 * Evénement : Modification du komi.
 * @param komi
 */
void EcranOptions_eventSetKomi(int komi);

/**
 * Evénement : Modification de la valeur du handicap.
 * @param handicap
 */
void EcranOptions_eventSetHandicap(int handicap);

/**
 * Evénement : modification du type d'un joueur.
 * @param joueur Le joueur à modifier.
 * @param type Type de joueur.
 */
void EcranOptions_eventSetTypeJoueur(Couleur joueur, TypeJoueur type);

/**
 * Evénement : modification du nom d'un joueur.
 * @param joueur Le joueur à modifier.
 * @param nom Nouveau nom.
 */
void EcranOptions_eventSetNomJoueur(Couleur joueur, char* nom);

/**
 * Evénement : modification du joueur affecté par le handicap.
 * @param joueur
 */
void EcranOptions_eventSetJoueurHandicap(Couleur joueur);

/**
 * Evénement : modification de la taille du plateau.
 * @param taille
 */
void EcranOptions_eventSetTaille(int taille);

/**
 * Evénement : début de la partie.
 */
void EcranOptions_eventCommencer();

#endif
