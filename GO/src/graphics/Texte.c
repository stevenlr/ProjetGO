/**
 * @file Texte.c
 * @brief 
 */

#include <stdlib.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "include/graphics/Texte.h"

#define TAILLE_NORMAL 21
#define TAILLE_GRAND 42

static TTF_Font* registreFontes[8];

int Texte_chargerFontes()
{
	int i, ok = 1;

	TTF_Init();

	registreFontes[NORMAL] = TTF_OpenFont("assets/fontes/Sansation_Regular.ttf", TAILLE_NORMAL);
	registreFontes[GRAS] = TTF_OpenFont("assets/fontes/Sansation_Bold.ttf", TAILLE_NORMAL);
	registreFontes[ITALIQUE] = TTF_OpenFont("assets/fontes/Sansation_Italic.ttf", TAILLE_NORMAL);
	registreFontes[GRAS | ITALIQUE] = TTF_OpenFont("assets/fontes/Sansation_Bold_Italic.ttf", TAILLE_NORMAL);
	registreFontes[GRAND | NORMAL] = TTF_OpenFont("assets/fontes/Sansation_Regular.ttf", TAILLE_GRAND);
	registreFontes[GRAND | GRAS] = TTF_OpenFont("assets/fontes/Sansation_Bold.ttf", TAILLE_GRAND);
	registreFontes[GRAND | ITALIQUE] = TTF_OpenFont("assets/fontes/Sansation_Italic.ttf", TAILLE_GRAND);
	registreFontes[GRAND | GRAS | ITALIQUE] = TTF_OpenFont("assets/fontes/Sansation_Bold_Italic.ttf", TAILLE_GRAND);

	for(i = 0; i < 8; i++)
	{
		if(registreFontes[i] == NULL)
		{
			fprintf(stderr, "Erreur de chargement de la fonte %d.\n", i);
			ok = 0;
		}
	}

	return ok;
}

void Texte_libererFontes()
{
	int i;

	for(i = 0; i < 8; i++)
	{
		if(registreFontes[i] != NULL)
			TTF_CloseFont(registreFontes[i]);
	}

	TTF_Quit();
}

void Texte_afficherChaine(SDL_Surface* surface, int x, int y, char* chaine, StyleTexte style, int couleur, AlignementTexte alignement)
{
	SDL_Color couleurSDL;
	SDL_Surface* texte;
	SDL_Rect rect;
	int tailleX, tailleY;

	couleurSDL.r = (couleur >> 4) & 0xff;
	couleurSDL.g = (couleur >> 2) & 0xff;
	couleurSDL.b = (couleur) & 0xff;

	rect.x = x;
	rect.y = y;

	texte = TTF_RenderText_Blended(registreFontes[style], chaine, couleurSDL);

	if(!texte)
		return;

	tailleX = texte->w;
	tailleY = texte->h;

	if(alignement & CENTRE_Y)
		rect.y -= tailleY / 2;

	if(alignement & CENTRE_X)
		rect.x -= tailleX / 2;
	else if(alignement & DROITE)
		rect.x -= tailleX;

	SDL_BlitSurface(texte, NULL, surface, &rect);

	SDL_FreeSurface(texte);
}
