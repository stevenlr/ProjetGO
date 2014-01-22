/**
 * @file InterfaceConsole.h
 * @brief 
 */

#ifndef INTERFACECONSOLE_H_
#define INTERFACECONSOLE_H_

#include "include/modes/etats/EtatsJeu.h"
#include "include/modes/etats/EtatsMenu.h"

void InterfaceConsole_entreeJeu(EtatsJeu* etats);
void InterfaceConsole_sortieJeu(EtatsJeu* etats);
void InterfaceConsole_entreeMenu(EtatsMenu* etats);
void InterfaceConsole_sortieMenu(EtatsMenu* etats);

#endif
