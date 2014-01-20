/**
 * @file Bouton.c
 * @brief 
 */

#include <stdlib.h>
#include <assert.h>

#include <SDL/SDL.h>

#include "include/graphics/Texte.h"
#include "include/graphics/Bouton.h"

Bouton Bouton_creer(char* texte, int x1, int x2, int y1, int y2, int couleurBouton, int couleurTexte)
{
	Bouton bouton;
	SDL_Rect rect;

	rect.x = x1;
	rect.y = y1;
	rect.w = x2 - x1;
	rect.h = y2 - y1;

	bouton.texte = texte;
	bouton.rect = rect;
	bouton.couleurBouton = couleurBouton;
	bouton.couleurTexte = couleurTexte;

	return bouton;
}

void Bouton_afficher(Bouton *bouton, SDL_Surface* surface)
{
	SDL_FillRect(surface, &(bouton->rect), bouton->couleurBouton);
	Texte_afficherChaine(surface, bouton->rect.x + bouton->rect.w / 2, bouton->rect.y + bouton->rect.h / 2,
			bouton->texte, NORMAL, bouton->couleurTexte, CENTRE_X | CENTRE_Y);
}

int Bouton_clique(Bouton *bouton, int x, int y)
{
	int x1, x2, y1, y2;

	x1 = bouton->rect.x;
	y1 = bouton->rect.y;
	x2 = x1 + bouton->rect.w;
	y2 = y1 + bouton->rect.h;

	return x >= x1 && y >= y1 && x <= x2 && y <= y2;
}
