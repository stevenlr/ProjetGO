/**
 * @file ContexteGraphique.h
 * @brief 
 */

#ifndef CONTEXTEGRAPHIQUE_H_
#define CONTEXTEGRAPHIQUE_H_

#include <SDL/SDL.h>

#include "Contexte.h"
#include "include/graphics/Bouton.h"

#define NBOUTONS 3

typedef enum {
	JEU_PASSER,
	JEU_SAUVEGARDER,
	JEU_QUITTER
} Boutons;

Bouton boutons[NBOUTONS];

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
