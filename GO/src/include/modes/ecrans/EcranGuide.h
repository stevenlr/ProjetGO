/**
 * @file EcranGuide.h
 * @brief 
 */

#ifndef ECRANGUIDE_H_
#define ECRANGUIDE_H_

int EcranGuide_init();
void EcranGuide_detruire();

void EcranGuide_main();

FonctionEntreeEcran EcranGuide_getEntreeFct();
FonctionSortieEcran EcranGuide_getSortieFct();

void EcranGuide_eventQuitter(int menu);
void EcranGuide_eventPrecedent();
void EcranGuide_eventSuivant();

#endif
