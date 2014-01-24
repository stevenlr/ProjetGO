/**
 * @file EcranJeu.h
 * @brief 
 */

#ifndef ECRANJEU_H_
#define ECRANJEU_H_

#include "Ecran.h"

void EcranJeu_init();
int EcranJeu_initCharger();
void EcranJeu_detruire();

void EcranJeu_main();

FonctionEntreeEcran EcranJeu_getEntreeFct();
FonctionSortieEcran EcranJeu_getSortieFct();

/**
 *
 * @param menu 1 si on soit revenir au menu, 0 sinon.
 */
void EcranJeu_eventArreter(int menu);
int EcranJeu_eventPlacerPion(int cx, int cy);
void EcranJeu_eventPasserTour();
void EcranJeu_eventSauvegarder();
void EcranJeu_eventSuivant();
void EcranJeu_eventPrecedent();

#endif
