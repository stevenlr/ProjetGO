/**
 * @file ContexteSDL.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <SDL/SDL.h>

#include "include/graphics/Bouton.h"
#include "include/graphics/Texture.h"
#include "include/graphics/Texte.h"

#include "include/modes/contextes/Contexte.h"
#include "include/modes/contextes/ContexteGraphique.h"

struct ContexteGraphique {
	SDL_Surface* window;
	int tailleX, tailleY;
};

Bouton boutons[NBOUTONS];

ContexteGraphique ContexteGraphique_creer()
{
	int milieu, bordGauche, bordDroit, tailleX = 1066, tailleY = 600;
	ContexteGraphique ctx;

	ctx = (ContexteGraphique) malloc(sizeof(struct ContexteGraphique));

	if(ctx == NULL)
		return NULL;

	ctx->tailleX = tailleX;
	ctx->tailleY = tailleY;

	bordGauche = tailleY;
	bordDroit = tailleX - 15;
	milieu = bordGauche + (bordDroit - bordGauche) / 2;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Erreur d'initialisation SDL.\n");
		free(ctx);
		return NULL;
	}

	SDL_WM_SetCaption("Jeu de Go", NULL);

	ctx->window = SDL_SetVideoMode(ctx->tailleX, ctx->tailleY, 24, SDL_HWSURFACE);
	if(ctx->window == NULL)
	{
		fprintf(stderr, "Erreur de creation de la fenetre.\n");
		free(ctx);
		return NULL;
	}

	if(!Texte_chargerFontes())
	{
		Texte_libererFontes();
		SDL_Quit();
		free(ctx);
		return NULL;
	}

	if(!Texture_chargerRegistre())
	{
		Texte_libererFontes();
		Texture_libererRegistre();
		SDL_Quit();
		free(ctx);
		return NULL;
	}

	boutons[PASSER] = Bouton_creer("Passer", bordGauche, bordDroit, 300, 330, 0x606060, 0xeeeeee);
	boutons[SAUVEGARDER] = Bouton_creer("Sauvegarder", bordGauche, milieu - 7, tailleY - 45, tailleY - 15, 0x606060, 0xeeeeee);
	boutons[QUITTER] = Bouton_creer("Quitter", milieu + 7, bordDroit, tailleY - 45, tailleY - 15, 0x803030, 0xeeeeee);

	return ctx;
}

void ContexteGraphique_detruire(ContexteGraphique ctx)
{
	assert(ctx);

	Texte_libererFontes();
	Texture_libererRegistre();
	SDL_Quit();
	free(ctx);
}

SDL_Surface* ContexteGraphique_getWindow()
{
	return ((ContexteGraphique) Contexte_get())->window;
}

int ContexteGraphique_getTailleX()
{
	return ((ContexteGraphique) Contexte_get())->tailleX;
}

int ContexteGraphique_getTailleY()
{
	return ((ContexteGraphique) Contexte_get())->tailleY;
}
