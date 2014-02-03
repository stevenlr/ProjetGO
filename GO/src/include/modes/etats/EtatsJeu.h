/**
 * @file EtatsJeu.h
 * @brief 
 */

#ifndef ETATSJEU_H_
#define ETATSJEU_H_

#include "include/Partie.h"

/**
 * Etats de l'écran de jeu.
 */
typedef struct {
	int continuer;			//!< 1 tant qu'on doit continuer sur cet écran.
	int estFini;			//!< 0 tant que la partie n'est pas finie et qu'on a pas encore calculé les scores.
	float scoreNoir;		//!< Score du joueur noir.
	float scoreBlanc;		//!< Score du joueur blanc.
	int premiereBoucle;		//!< 1 si c'est la première boucle de la logique du jeu.
	int derniereBoucle;		//!< 1 si c'est la dernière boucle avant fermeture de l'écran.
	Partie partie;			//!< Partie actuelle.
} EtatsJeu;

#endif
