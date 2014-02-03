/**
 * @file EtatsOptions.h
 * @brief
 */

#ifndef ETATSOPTIONS_H_
#define ETATSOPTIONS_H_

#include "include/Couleur.h"
#include "include/Partie.h"

/**
 * Etats de l'�cran d'options.
 */
typedef struct {
	int continuer;			//!< 1 tant qu'on doit continuer sur cet �cran.
	char nomJ1[17];			//!< Nom du joueur 1.
	char nomJ2[17];			//!< Nom du joueur 2.
	TypeJoueur typeJ1;		//!< Type du joueur 1.
	TypeJoueur typeJ2;		//!< Type du joueur 2.
	int handicap;			//!< Valeur du handicap.
	Couleur joueurHandicap;	//!< Joueur auquel s'applique le handicap.
	int komi;				//!< Valeur du komi - 0.5
	int taille;				//!< Taille du plateau.
	int derniereBoucle;		//!< 1 si c'est la derni�re boucle avant fermeture de l'�cran.
	int premiereBoucle;		//!< 1 si c'est la premi�re boucle de la logique de l'�cran.
} EtatsOptions;

#endif
