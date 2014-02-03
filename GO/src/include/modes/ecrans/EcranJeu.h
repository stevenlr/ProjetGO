/**
 * @file EcranJeu.h
 * @brief Ecran de jeu.
 */

#ifndef ECRANJEU_H_
#define ECRANJEU_H_

#include "include/Partie.h"
#include "Ecran.h"

/**
 * Initialise l'écran de jeu à partir des options de jeu passées.
 *
 * @param nomJ1 Nom de J1.
 * @param nomJ2 Nom du J2.
 * @param typeJ1 Type du J1.
 * @param typeJ2 Type du J2.
 * @param taille Taille du plateau.
 * @param handicap Valeur du handicap. 0 = sans ; +X = Noir ; -X = Blanc ; X = nombre de coups d'avance.
 * @param komi valeur du komi.
 * @return 0 en cas d'erreur, 1 sinon.
 */
int EcranJeu_init(char* nomJ1, char* nomJ2, TypeJoueur typeJ1, TypeJoueur typeJ2, int taille, int handicap, float komi);

/**
 * Initialise l'écran de jeu depuis la dernière partie enregistrée.
 *
 * @return 0 si on n'a pas pu charger la dernière partie, 1 sinon.
 */
int EcranJeu_initCharger();

/**
 * Détruit les états de l'écran de jeu.
 */
void EcranJeu_detruire();

/**
 * Logique de l'écran de jeu.
 */
void EcranJeu_main();

/**
 * Retourne la fonction d'entrée de l'écran de jeu.
 * @return
 */
FonctionEntreeEcran EcranJeu_getEntreeFct();

/**
 * Retourne la fonction de sortie de l'écran de jeu.
 * @return
 */
FonctionSortieEcran EcranJeu_getSortieFct();

/**
 * Evénement : arrêt du jeu.
 * @param menu 1 si on soit revenir au menu, 0 si on doit fermer le jeu.
 */
void EcranJeu_eventArreter(int menu);

/**
 * Evénement : placement du pion sur le plateau.
 *
 * @param cx Coordonnée x du pion sur le plateau.
 * @param cy Coordonnée y du pion sur le plateau.
 * @return 1 si on a bien pu le placer, 0 si le coup n'était pas valide.
 */
int EcranJeu_eventPlacerPion(int cx, int cy);

/**
 * Evénement : le joueur actuel passe son tour.
 */
void EcranJeu_eventPasserTour();

/**
 * Evénement : sauvegarde de la partie actuelle.
 */
void EcranJeu_eventSauvegarder();

/**
 * Evénement : aller au plateau suivant.
 */
void EcranJeu_eventSuivant();

/**
 * Evénement : aller au plateau précédent.
 */
void EcranJeu_eventPrecedent();

#endif
