/**
 * @file ContexteGraphique.h
 * @brief 
 */

#ifndef CONTEXTEGRAPHIQUE_H_
#define CONTEXTEGRAPHIQUE_H_

#include <SDL/SDL.h>

#include "Contexte.h"
#include "include/graphics/Bouton.h"
#include "include/graphics/ChoixMultiple.h"

#define NBOUTONS 18

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
	GUIDE_SUIVANT,

	OPTIONS_RETOUR,
	OPTIONS_COMMENCER,
	OPTIONS_HANDICAP_MOINS,
	OPTIONS_HANDICAP_PLUS,
	OPTIONS_KOMI_MOINS,
	OPTIONS_KOMI_PLUS
} Boutons;

Bouton boutons[NBOUTONS];

#define NCHOIXMULTIPLES 4

typedef enum {
	OPTIONS_TYPEJ1,
	OPTIONS_TYPEJ2,
	OPTIONS_HANDICAP,
	OPTIONS_TAILLE
} ChoixMultiples;

ChoixMultiple choixMultiples[NCHOIXMULTIPLES];

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
