/**
 * @file Partie.h
 * @brief 
 */

#ifndef PARTIE_H_
#define PARTIE_H_

#include "include/Plateau.h"
#include "include/Couleur.h"

typedef struct Partie* Partie;

/**
 * Creer une partie avec les paramètres suivant. Inserer un plateau vide (plateau de départ).
 *
 * @param joueurNoir	: Pseudonyme
 * @param joueurBlanc	: Pseudonyme
 * @param komi 		: Komi choisi au départ
 * @param handicap 	: 0 = sans ; +X = Noir ; -X = Blanc ; X = nombre de coups d'avance.
 * @param taille 	: Taille du plateau
 * @return partie
 */
Partie Partie_creer(char* joueurNoir, char* joueurBlanc, float komi, int handicap, int taille);

/**
 * Désalloue une partie
 *
 * @param partie
 */
void Partie_detruire(Partie partie);

/**
 * Renvoie l'handicap actuel de la partie.
 *
 * @param partie
 * @return handicap : 0 une fois qu'il y en a plus/pas.
 */
int Partie_getHandicap(Partie partie);

/**
 * Renvoie le komi de la partie
 *
 * @param partie
 * @return komi
 */
float Partie_getKomi(Partie partie);

/**
 * Renvoie la taille du goban.
 *
 * @param partie
 * @return taille
 */
int Partie_getTaille(Partie partie);

/**
 * Met dans joueur le pseudo du Joueur correspondant à couleur.
 *
 * @param partie
 * @param couleur
 * @param joueur
 */
void Partie_getJoueur(Partie partie, Couleur couleur, char* joueur);

/**
 * Renvoie la couleur du joueur actuel
 *
 * @param partie
 * @return
 */
Couleur Partie_getJoueurActuel(Partie partie);

/**
 * Passe au joueur suivant, sauf s'il y a encore un handicap.
 *
 * @param partie
 */
void Partie_changeJoueurActuel(Partie partie);

/**
 * Renvoie le plateau actuel.
 *
 * @param partie
 * @return plateau
 */
Plateau Partie_getPlateauActuel(Partie partie);

/**
 * Insere un plateau dans la liste des plateaux de la partie.
 *
 * @param partie
 * @param plateau
 */
void Partie_insererPlateau(Partie partie, Plateau plateau);

/**
 * Calcule le score de la partie.
 *
 * @param plateau
 * @param komi
 * @param scoreNoir
 * @param scoreBlanc
 */
void Partie_calculerScore(Partie partie, float* scoreNoir, float* scoreBlanc);

/**
 * Passe un tour.
 *
 * @param partie
 */
void Partie_passerTour(Partie partie);

/**
 * Joue un tour normal.
 *
 * @param partie
 */
void Partie_jouerTour(Partie partie);

/**
 * Vérifie si la partie est finie.
 *
 * @param partie
 * @return 1 si la partie est finie, 0 sinon.
 */
int Partie_estFinie(Partie partie);

/**
 * Sauvegarde une Partie de le FILE "fichier"
 *
 * @param partie
 * @param fichier
 * @return 0 si echec, sinon 1.
 */
int Partie_sauvegarder(Partie partie, FILE* fichier);

/**
 * Charge une partie via le FILE "fichier"
 *
 * @param fichier
 * @return NULL si echec, la partie chargée sinon.
 */
Partie Partie_charger(FILE* fichier);

#endif
