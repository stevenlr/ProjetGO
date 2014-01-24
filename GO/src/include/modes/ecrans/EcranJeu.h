/**
 * @file EcranJeu.h
 * @brief 
 */

#ifndef ECRANJEU_H_
#define ECRANJEU_H_

#include "include/Partie.h"
#include "Ecran.h"

int EcranJeu_init(char* nomJ1, char* nomJ2, TypeJoueur typeJ1, TypeJoueur typeJ2, int taille, int handicap, float komi);
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
