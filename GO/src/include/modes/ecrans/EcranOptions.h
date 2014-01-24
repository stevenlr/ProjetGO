/**
 * @file EcranOptions.h
 * @brief 
 */

#ifndef ECRANOPTIONS_H_
#define ECRANOPTIONS_H_

#include "include/Couleur.h"
#include "include/Partie.h"

#include "Ecran.h"

void EcranOptions_init();
void EcranOptions_detruire();

void EcranOptions_main();

FonctionEntreeEcran EcranOptions_getEntreeFct();
FonctionSortieEcran EcranOptions_getSortieFct();

void EcranOptions_eventQuitter(int menu);
void EcranOptions_eventSetKomi(int komi);
void EcranOptions_eventSetHandicap(int handicap);
void EcranOptions_eventSetTypeJoueur(Couleur joueur, TypeJoueur type);
void EcranOptions_eventSetJoueurHandicap(Couleur joueur);
void EcranOptions_eventSetTaille(int taille);
void EcranOptions_eventCommencer();

#endif
