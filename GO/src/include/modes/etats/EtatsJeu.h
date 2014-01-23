/**
 * @file EtatsJeu.h
 * @brief 
 */

#ifndef ETATSJEU_H_
#define ETATSJEU_H_

#include "include/Partie.h"

typedef struct {
	int continuer;
	int estFini;	// 0 tant que la partie n'est pas finie et qu'on a pas encore calculé les scores.
	float scoreNoir, scoreBlanc;
	int premiereBoucle;
	int derniereBoucle;
	Partie partie;
} EtatsJeu;

#endif
