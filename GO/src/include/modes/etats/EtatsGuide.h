/**
 * @file EtatsGuide.h
 * @brief 
 */

#ifndef ETATSGUIDE_H_
#define ETATSGUIDE_H_

#include "include/Tutoriel.h"

/**
 * Etats de l'écran de tutoriel.
 */
typedef struct {
	int continuer;			//!< 1 tant qu'on doit rester sur lécran courant.
	int besoinRafraichir;	//!< 1 si les modifications nécessites de rafraîchir l'affichage.
	int premiereBoucle;		//!< 1 si c'est la première boucle de la logique du jeu.
	int derniereBoucle;		//!< 1 si c'est la dernière boucle avant fermeture de l'écran.
	Tutoriel tutoriel;		//!< Instance du tutoriel.
} EtatsGuide;

#endif
