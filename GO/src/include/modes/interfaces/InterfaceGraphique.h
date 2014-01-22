/**
 * @file InterfaceGraphique.h
 * @brief 
 */

#ifndef INTERFACEGRAPHIQUE_H_
#define INTERFACEGRAPHIQUE_H_

#include "include/modes/etats/EtatsJeu.h"
#include "include/modes/etats/EtatsMenu.h"

#define TAILLE_CELL 30

void InterfaceGraphique_entreeJeu(EtatsJeu* etats);
void InterfaceGraphique_sortieJeu(EtatsJeu* etats);

void InterfaceGraphique_entreeMenu(EtatsMenu* etats);
void InterfaceGraphique_sortieMenu(EtatsMenu* etats);

#endif
