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
 * Type de joueur.
 */
typedef enum {
	HUMAIN,   //!< HUMAIN
	ORDINATEUR//!< ORDINATEUR
} TypeJoueur;

/**
 * Creer une partie avec les param�tres suivant. Inserer un plateau vide (plateau de d�part).
 *
 * @param joueurNoir	: Pseudonyme
 * @param joueurBlanc	: Pseudonyme
 * @param komi 		: Komi choisi au d�part
 * @param handicap 	: 0 = sans ; +X = Noir ; -X = Blanc ; X = nombre de coups d'avance.
 * @param taille 	: Taille du plateau
 * @return partie
 */
Partie Partie_creer(char* joueurNoir, char* joueurBlanc, TypeJoueur typeNoir, TypeJoueur typeBlanc, float komi, int handicap, int taille);

/**
 * D�salloue une partie
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
 * Renvoie le tour.
 *
 * @param partie
 * @return tour
 */
int Partie_getTour(Partie partie);

/**
 * Met dans joueur le pseudo du Joueur correspondant � couleur.
 *
 * @param partie
 * @param couleur
 * @return Nom du joueur
 */
char* Partie_getJoueur(Partie partie, Couleur couleur);

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
 * V�rifie si un plateau a d�j� �t� jou�.
 *
 * @param partie
 * @param plateau
 * @return 1 si un plateau identique a exist�, 0 sinon.
 */
int Partie_appartientPlateau(Partie partie, Plateau plateau);

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
 * V�rifie si la partie est finie.
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
 * @return NULL si echec, la partie charg�e sinon.
 */
Partie Partie_charger(FILE* fichier);

/**
 * V�rifie si on est actuellement au premier plateau de la partie.
 *
 * @param partie
 * @return 1 si on est est premier. 0 sinon.
 */
int Partie_estAuPremier(Partie partie);

/**
 * V�rifie si on est actuellement au dernier plateau de la partie.
 *
 * @param partie
 * @return 1 si on est est dernier. 0 sinon.
 */
int Partie_estAuDernier(Partie partie);

/**
 * Revient au plateau pr�c�dent.
 *
 * @param partie
 */
void Partie_rembobiner(Partie partie);

/**
 * Avance d'un plateau dans la partie.
 *
 * @param partie
 */
void Partie_avancer(Partie partie);

/**
 * Supprime tous les plateaux apr�s le courant.
 *
 * @param partie.
 */
void Partie_supprimerPlateauxSuivants(Partie partie);

#endif
