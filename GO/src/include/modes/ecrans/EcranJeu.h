/**
 * @file EcranJeu.h
 * @brief Ecran de jeu.
 */

#ifndef ECRANJEU_H_
#define ECRANJEU_H_

#include "include/Partie.h"
#include "Ecran.h"

/**
 * Initialise l'�cran de jeu � partir des options de jeu pass�es.
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
 * Initialise l'�cran de jeu depuis la derni�re partie enregistr�e.
 *
 * @return 0 si on n'a pas pu charger la derni�re partie, 1 sinon.
 */
int EcranJeu_initCharger();

/**
 * D�truit les �tats de l'�cran de jeu.
 */
void EcranJeu_detruire();

/**
 * Logique de l'�cran de jeu.
 */
void EcranJeu_main();

/**
 * Retourne la fonction d'entr�e de l'�cran de jeu.
 * @return
 */
FonctionEntreeEcran EcranJeu_getEntreeFct();

/**
 * Retourne la fonction de sortie de l'�cran de jeu.
 * @return
 */
FonctionSortieEcran EcranJeu_getSortieFct();

/**
 * Ev�nement : arr�t du jeu.
 * @param menu 1 si on soit revenir au menu, 0 si on doit fermer le jeu.
 */
void EcranJeu_eventArreter(int menu);

/**
 * Ev�nement : placement du pion sur le plateau.
 *
 * @param cx Coordonn�e x du pion sur le plateau.
 * @param cy Coordonn�e y du pion sur le plateau.
 * @return 1 si on a bien pu le placer, 0 si le coup n'�tait pas valide.
 */
int EcranJeu_eventPlacerPion(int cx, int cy);

/**
 * Ev�nement : le joueur actuel passe son tour.
 */
void EcranJeu_eventPasserTour();

/**
 * Ev�nement : sauvegarde de la partie actuelle.
 */
void EcranJeu_eventSauvegarder();

/**
 * Ev�nement : aller au plateau suivant.
 */
void EcranJeu_eventSuivant();

/**
 * Ev�nement : aller au plateau pr�c�dent.
 */
void EcranJeu_eventPrecedent();

#endif
