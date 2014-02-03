/**
 * @file EtatsGuide.h
 * @brief 
 */

#ifndef ETATSGUIDE_H_
#define ETATSGUIDE_H_

#include "include/Tutoriel.h"

/**
 * Etats de l'�cran de tutoriel.
 */
typedef struct {
	int continuer;			//!< 1 tant qu'on doit rester sur l�cran courant.
	int besoinRafraichir;	//!< 1 si les modifications n�cessites de rafra�chir l'affichage.
	int premiereBoucle;		//!< 1 si c'est la premi�re boucle de la logique du jeu.
	int derniereBoucle;		//!< 1 si c'est la derni�re boucle avant fermeture de l'�cran.
	Tutoriel tutoriel;		//!< Instance du tutoriel.
} EtatsGuide;

#endif
