/**
 * @file EcranJeu.h
 * @brief 
 */

#ifndef ECRANJEU_H_
#define ECRANJEU_H_

#include "Ecran.h"

void EcranJeu_init();
void EcranJeu_detruire();

void EcranJeu_main();

FonctionEntreeEcran EcranJeu_getEntreeFct();
FonctionSortieEcran EcranJeu_getSortieFct();

void EcranJeu_eventArreter();
void EcranJeu_eventPlacerPion(int cx, int cy);

#endif
