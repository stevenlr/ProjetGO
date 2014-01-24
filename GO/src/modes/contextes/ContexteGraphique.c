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

#define BASE_BOUTONS_MENU 200

struct ContexteGraphique {
	SDL_Surface* window;
	SDL_Surface* icon;
	int tailleX, tailleY;
};

Bouton boutons[NBOUTONS];

ContexteGraphique ContexteGraphique_creer()
{
	int milieu, bordGauche, bordDroit, tailleX = 1066, tailleY = 600, i;
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

	ctx->icon = SDL_LoadBMP("assets/images/icon.bmp");

	SDL_WM_SetIcon(ctx->icon, NULL);
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

	boutons[JEU_PASSER] = Bouton_creer("Passer", bordGauche, bordDroit, 265, 305, 0x606060, 0xeeeeee);
	boutons[JEU_SAUVEGARDER] = Bouton_creer("Sauvegarder", bordGauche, milieu - 7, tailleY - 55, tailleY - 15, 0x606060, 0xeeeeee);
	boutons[JEU_QUITTER] = Bouton_creer("Quitter", milieu + 7, bordDroit, tailleY - 55, tailleY - 15, 0x803030, 0xeeeeee);
	boutons[JEU_PRECEDENT] = Bouton_creer("<", bordGauche, milieu - 100, 320, 360, 0x606060, 0xeeeeee);
	boutons[JEU_SUIVANT] = Bouton_creer(">", milieu + 100, bordDroit, 320, 360, 0x606060, 0xeeeeee);

	boutons[MENU_NOUVELLEPARTIE] = Bouton_creer("Nouvelle partie", 533 - 200, 533 + 200, BASE_BOUTONS_MENU, BASE_BOUTONS_MENU + 40, 0xd0d0d0, 0x505050);
	boutons[MENU_REPRENDREPARTIE] = Bouton_creer("Reprendre une partie", 533 - 200, 533 + 200, BASE_BOUTONS_MENU + 60, BASE_BOUTONS_MENU + 100, 0xd0d0d0, 0x505050);
	boutons[MENU_GUIDE] = Bouton_creer("Comment jouer ?", 533 - 200, 533 + 200, BASE_BOUTONS_MENU + 120, BASE_BOUTONS_MENU + 160, 0xd0d0d0, 0x505050);
	boutons[MENU_QUITTER] = Bouton_creer("Quitter", 533 - 200, 533 + 200, BASE_BOUTONS_MENU + 260, BASE_BOUTONS_MENU + 300, 0xd0d0d0, 0x505050);

	boutons[GUIDE_QUITTER] = Bouton_creer("Retour", 15, 215, 15, 55, 0x606060, 0xeeeeee);
	boutons[GUIDE_PRECEDENT] = Bouton_creer("<", 533 - 15 - 100, 533 - 15, 15, 55, 0x606060, 0xeeeeee);
	boutons[GUIDE_SUIVANT] = Bouton_creer(">", 533 + 15, 533 + 15 + 100, 15, 55, 0x606060, 0xeeeeee);

	boutons[OPTIONS_RETOUR] = Bouton_creer("Retour", 15, 215, 15, 55, 0x606060, 0xeeeeee);
	boutons[OPTIONS_COMMENCER] = Bouton_creer("Commencer", 15, 215, 600 - 55, 600 - 15, 0x606060, 0xeeeeee);

	boutons[OPTIONS_KOMI_MOINS] = Bouton_creer("-", 300, 350, 345, 385, 0x606060, 0xeeeeee);
	boutons[OPTIONS_KOMI_PLUS] = Bouton_creer("+", 450, 500, 345, 385, 0x606060, 0xeeeeee);

	boutons[OPTIONS_HANDICAP_MOINS] = Bouton_creer("-", 300, 350, 420, 460, 0x606060, 0xeeeeee);
	boutons[OPTIONS_HANDICAP_PLUS] = Bouton_creer("+", 450, 500, 420, 460, 0x606060, 0xeeeeee);

	for(i = 0; i < NBOUTONS; i++)
	{
		if(boutons[i] == NULL)
		{
			fprintf(stderr, "Erreur de création du bouton %d.\n", i);
			ContexteGraphique_detruire(ctx);
			return NULL;
		}
	}

	choixMultiples[OPTIONS_TYPEJ1] = ChoixMultiple_creer(600, 120, 130, 0x303030, 0x606060, 0xeeeeee);
	choixMultiples[OPTIONS_TYPEJ2] = ChoixMultiple_creer(600, 195, 130, 0x303030, 0x606060, 0xeeeeee);
	choixMultiples[OPTIONS_HANDICAP] = ChoixMultiple_creer(530, 420, 120, 0x303030, 0x606060, 0xeeeeee);
	choixMultiples[OPTIONS_TAILLE] = ChoixMultiple_creer(300, 270, 80, 0x303030, 0x606060, 0xeeeeee);

	for(i = 0; i < NCHOIXMULTIPLES; i++)
	{
		if(choixMultiples[i] == NULL)
		{
			fprintf(stderr, "Erreur de création du choix multiple %d.\n", i);
			ContexteGraphique_detruire(ctx);
			return NULL;
		}
	}

	ChoixMultiple_ajouterChoix(choixMultiples[OPTIONS_TYPEJ1], "Humain");
	ChoixMultiple_ajouterChoix(choixMultiples[OPTIONS_TYPEJ1], "Ordinateur");

	ChoixMultiple_ajouterChoix(choixMultiples[OPTIONS_TYPEJ2], "Humain");
	ChoixMultiple_ajouterChoix(choixMultiples[OPTIONS_TYPEJ2], "Ordinateur");

	ChoixMultiple_ajouterChoix(choixMultiples[OPTIONS_HANDICAP], "Joueur 1");
	ChoixMultiple_ajouterChoix(choixMultiples[OPTIONS_HANDICAP], "Joueur 2");

	ChoixMultiple_ajouterChoix(choixMultiples[OPTIONS_TAILLE], "9");
	ChoixMultiple_ajouterChoix(choixMultiples[OPTIONS_TAILLE], "13");
	ChoixMultiple_ajouterChoix(choixMultiples[OPTIONS_TAILLE], "19");

	return ctx;
}

void ContexteGraphique_detruire(ContexteGraphique ctx)
{
	int i;

	assert(ctx);

	for(i = 0; i < NBOUTONS; i++)
	{
		if(boutons[i] != NULL)
			Bouton_detruire(boutons[i]);
	}

	for(i = 0; i < NCHOIXMULTIPLES; i++)
	{
		if(choixMultiples[i] != NULL)
			ChoixMultiple_detruire(choixMultiples[i]);
	}

	Texte_libererFontes();
	Texture_libererRegistre();
	SDL_FreeSurface(ctx->icon);
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
