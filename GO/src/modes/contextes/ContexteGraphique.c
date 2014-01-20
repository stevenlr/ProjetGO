/**
 * @file ContexteSDL.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <SDL/SDL.h>

#include "include/graphics/Texture.h"
#include "include/graphics/Texte.h"

#include "include/modes/contextes/Contexte.h"
#include "include/modes/contextes/ContexteGraphique.h"

struct ContexteGraphique {
	SDL_Surface* window;
	int tailleX, tailleY;
};

ContexteGraphique ContexteGraphique_creer()
{
	ContexteGraphique ctx;

	ctx = (ContexteGraphique) malloc(sizeof(struct ContexteGraphique));

	if(ctx == NULL)
		return NULL;

	ctx->tailleX = 1066;
	ctx->tailleY = 600;

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
