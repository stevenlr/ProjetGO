/**
 * @file EtatsOptions.h
 * @brief
 */

#ifndef ETATSOPTIONS_H_
#define ETATSOPTIONS_H_

#include "include/Couleur.h"
#include "include/Partie.h"

typedef struct {
	int continuer;
	char nomJ1[17], nomJ2[17];
	TypeJoueur typeJ1, typeJ2;
	int handicap;
	Couleur joueurHandicap;
	int komi;
	int taille;
	int derniereBoucle;
	int premiereBoucle;
} EtatsOptions;

#endif