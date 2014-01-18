/**
 * @file ContexteGraphique.h
 * @brief 
 */

#ifndef CONTEXTEGRAPHIQUE_H_
#define CONTEXTEGRAPHIQUE_H_

#include <SDL/SDL.h>
#include "Contexte.h"

typedef struct ContexteGraphique* ContexteGraphique;

/**
 * Crée un contexte en mode SDL.
 *
 * @return Le contexte créé.
 */
ContexteGraphique ContexteGraphique_creer();

/**
 * Détruit un contexte en mode SDL.
 *
 * @param Contexte à détruire
 */
void ContexteGraphique_detruire(ContexteGraphique ctx);

SDL_Surface* ContexteGraphique_getWindow();
int ContexteGraphique_getTailleX();
int ContexteGraphique_getTailleY();

#endif
