/**
 * @file ContexteGraphique.h
 * @brief 
 */

#ifndef CONTEXTEGRAPHIQUE_H_
#define CONTEXTEGRAPHIQUE_H_

#include <SDL/SDL.h>

#include "Contexte.h"
#include "include/graphics/Bouton.h"

#define NBOUTONS 12

typedef enum {
	JEU_PASSER,
	JEU_SAUVEGARDER,
	JEU_QUITTER,
	JEU_PRECEDENT,
	JEU_SUIVANT,

	MENU_NOUVELLEPARTIE,
	MENU_REPRENDREPARTIE,
	MENU_GUIDE,
	MENU_QUITTER,

	GUIDE_QUITTER,
	GUIDE_PRECEDENT,
	GUIDE_SUIVANT
} Boutons;

Bouton boutons[NBOUTONS];

typedef struct ContexteGraphique* ContexteGraphique;

/**
 * Cr�e un contexte en mode SDL.
 *
 * @return Le contexte cr��.
 */
ContexteGraphique ContexteGraphique_creer();

/**
 * D�truit un contexte en mode SDL.
 *
 * @param Contexte � d�truire
 */
void ContexteGraphique_detruire(ContexteGraphique ctx);

SDL_Surface* ContexteGraphique_getWindow();
int ContexteGraphique_getTailleX();
int ContexteGraphique_getTailleY();

#endif
