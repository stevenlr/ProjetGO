/**
 * @file EtatsJeu.h
 * @brief 
 */

#ifndef ETATSJEU_H_
#define ETATSJEU_H_

#include "include/Plateau.h"

typedef struct {
	int tour;
	int taillePlateau;
	int continuer;
	Plateau plateau;
} EtatsJeu;

#endif
