/**
 * @file EcranMenu.h
 * @brief 
 */

#ifndef ECRANMENU_H_
#define ECRANMENU_H_

#include "Ecran.h"

void EcranMenu_init();
void EcranMenu_detruire();

void EcranMenu_main();

FonctionEntreeEcran EcranMenu_getEntreeFct();
FonctionSortieEcran EcranMenu_getSortieFct();

void EcranMenu_eventQuitter();
void EcranMenu_eventReprendre();
void EcranMenu_eventNouvellePartie();

#endif
