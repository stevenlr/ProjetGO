/**
 * @file ChoixMultiple.c
 * @brief 
 */

#include <stdlib.h>
#include <assert.h>

#include <SDL/SDL.h>

#include "include/graphics/Texte.h"
#include "include/graphics/ChoixMultiple.h"

#define MAXCHOIX 3

struct ChoixMultiple {
	int nchoix;
	int choisi;
	int x, y, largeur;
	char texte[MAXCHOIX][17];
	int couleurNormal, couleurChoisi, couleurTexte;
};

ChoixMultiple ChoixMultiple_creer(int x, int y, int largeur, int couleurNormal, int couleurChoisi, int couleurTexte)
{
	ChoixMultiple cm;

	cm = malloc(sizeof(struct ChoixMultiple));
	if(cm == NULL)
		return NULL;

	cm->x = x;
	cm->y = y;
	cm->largeur = largeur;
	cm->couleurNormal = couleurNormal;
	cm->couleurChoisi = couleurChoisi;
	cm->couleurTexte = couleurTexte;
	cm->nchoix = 0;
	cm->choisi = 0;

	memset(cm->texte, 0, MAXCHOIX * 17);

	return cm;
}

void ChoixMultiple_ajouterChoix(ChoixMultiple cm, char* str)
{
	int len = strlen(str);

	if(cm->nchoix == MAXCHOIX)
		return;

	if(len > 16) len = 16;

	strncpy(cm->texte[cm->nchoix], str, len);
	cm->texte[cm->nchoix][len] = '\0';

	cm->nchoix++;
}

int ChoixMultiple_getCourant(ChoixMultiple cm)
{
	return cm->choisi;
}

void ChoixMultiple_setCourant(ChoixMultiple cm, int choisi)
{
	if(choisi < 0 || choisi >= cm->nchoix)
		return;

	cm->choisi = choisi;
}

void ChoixMultiple_afficher(ChoixMultiple cm, SDL_Surface* surface)
{
	int i;
	int x, y;
	int couleur;
	SDL_Rect rect;

	x = cm->x + cm->largeur / 2;
	y = cm->y + 20;

	rect.x = cm->x;
	rect.y = cm->y;
	rect.w = cm->largeur;
	rect.h = 40;

	for(i = 0; i < cm->nchoix; i++)
	{
		couleur = (i == cm->choisi) ? cm->couleurChoisi : cm->couleurNormal;

		SDL_FillRect(surface, &rect, couleur);
		Texte_afficherChaine(surface, x, y, cm->texte[i], NORMAL, cm->couleurTexte, CENTRE_X | CENTRE_Y);

		x += cm->largeur;
		rect.x += cm->largeur;
	}
}

int ChoixMultiple_clique(ChoixMultiple cm, int x, int y)
{
	int casex;

	if(y < cm->y || y > cm->y + 40 || x < cm->x)
		return 0;

	casex = (x - cm->x) / cm->largeur;

	if(casex < 0 || casex >= cm->nchoix)
		return 0;

	cm->choisi = casex;

	return 1;
}

void ChoixMultiple_detruire(ChoixMultiple cm)
{
	assert(cm);

	free(cm);
}
