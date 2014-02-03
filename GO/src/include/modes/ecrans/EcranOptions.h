/**
 * @file EcranOptions.h
 * @brief Ecran de cr�ation d'une partie.
 */

#ifndef ECRANOPTIONS_H_
#define ECRANOPTIONS_H_

#include "include/Couleur.h"
#include "include/Partie.h"

#include "Ecran.h"

/**
 * Initialise les �tats de l'�cran de cr�ation de partie.
 */
void EcranOptions_init();

/**
 * D�truit les �tats de l'�cran de cr�ation de partie.
 */
void EcranOptions_detruire();

/**
 * Logique de l'�cran de cr�ation de partie.
 */
void EcranOptions_main();

/**
 * Retourne la fonction d'entr�e correspondant au contexte courant pour l'�cran de cr�ation de partie.
 * @return
 */
FonctionEntreeEcran EcranOptions_getEntreeFct();

/**
 * Retourne la fonction de sortie correspondant au contexte courant pour l'�cran de cr�ation de partie.
 * @return
 */
FonctionSortieEcran EcranOptions_getSortieFct();

/**
 * Ev�nement : quitter l'�cran actuel.
 * @param menu 0 : on ferme le jeu, 1 : on revient � l'�cran d'accueil.
 */
void EcranOptions_eventQuitter(int menu);

/**
 * Ev�nement : Modification du komi.
 * @param komi
 */
void EcranOptions_eventSetKomi(int komi);

/**
 * Ev�nement : Modification de la valeur du handicap.
 * @param handicap
 */
void EcranOptions_eventSetHandicap(int handicap);

/**
 * Ev�nement : modification du type d'un joueur.
 * @param joueur Le joueur � modifier.
 * @param type Type de joueur.
 */
void EcranOptions_eventSetTypeJoueur(Couleur joueur, TypeJoueur type);

/**
 * Ev�nement : modification du nom d'un joueur.
 * @param joueur Le joueur � modifier.
 * @param nom Nouveau nom.
 */
void EcranOptions_eventSetNomJoueur(Couleur joueur, char* nom);

/**
 * Ev�nement : modification du joueur affect� par le handicap.
 * @param joueur
 */
void EcranOptions_eventSetJoueurHandicap(Couleur joueur);

/**
 * Ev�nement : modification de la taille du plateau.
 * @param taille
 */
void EcranOptions_eventSetTaille(int taille);

/**
 * Ev�nement : d�but de la partie.
 */
void EcranOptions_eventCommencer();

#endif
