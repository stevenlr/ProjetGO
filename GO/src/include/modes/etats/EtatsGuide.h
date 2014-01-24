/**
 * @file EtatsGuide.h
 * @brief 
 */

#ifndef ETATSGUIDE_H_
#define ETATSGUIDE_H_

#include "include/Tutoriel.h"

typedef struct {
	int continuer;
	int besoinRafraichir;
	int premiereBoucle;
	int derniereBoucle;
	Tutoriel tutoriel;
} EtatsGuide;

#endif
