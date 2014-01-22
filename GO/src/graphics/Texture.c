/**
 * @file Texture.c
 * @brief 
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "include/graphics/Texture.h"

/**
 * Texture
 */
struct Texture {
	int tailleX; 		/**< Largeur de la texture. */
	int tailleY;		/**< Hauteur de la texture. */
	SDL_Surface* image;	/**< Image. */
};

static Texture registreTextures[NB_TEXTURES];

// Fonctions privées ==========================================================

/**
 * Charge une texture depuis un fichier.
 *
 * @param fichier
 * @return La texture chargée. NULL en cas d'erreur.
 */
static Texture Texture_creer(const char* fichier);

/**
 * Détruit une texture.
 *
 * @param texture
 */
static void Texture_detruire(Texture texture);

Texture Texture_creer(const char* fichier)
{
	Texture texture;

	texture = (Texture) malloc(sizeof(struct Texture));

	if(texture == NULL)
		return NULL;

	texture->image = IMG_Load(fichier);

	if(texture->image == NULL)
	{
		free(texture);
		return NULL;
	}

	texture->tailleX = texture->image->w;
	texture->tailleY = texture->image->h;

	return texture;
}

void Texture_detruire(Texture texture)
{
	assert(texture);

	SDL_FreeSurface(texture->image);
	free(texture);
}

// Fonction publiques =========================================================

void Texture_blit(IdTexture idTexture, SDL_Surface* surface, int x, int y)
{
	SDL_Rect position;

	assert(idTexture >= 0 && idTexture < NB_TEXTURES);
	assert(surface);

	position.x = x;
	position.y = y;

	SDL_BlitSurface(registreTextures[idTexture]->image, NULL, surface, &position);
}

void Texture_blitCentre(IdTexture idTexture, SDL_Surface* surface, int centreX, int centreY)
{
	int x, y;

	assert(idTexture >= 0 && idTexture < NB_TEXTURES);
	assert(surface);

	x = centreX - registreTextures[idTexture]->tailleX / 2;
	y = centreY - registreTextures[idTexture]->tailleY / 2;

	Texture_blit(idTexture, surface, x, y);
}

int Texture_chargerRegistre()
{
	int i, status;

	registreTextures[TEXTURE_PION_BLANC] = Texture_creer("assets/images/pion_blanc.png");
	registreTextures[TEXTURE_PION_NOIR] = Texture_creer("assets/images/pion_noir.png");
	registreTextures[TEXTURE_PLATEAU_9] = Texture_creer("assets/images/plateau_9.png");
	registreTextures[TEXTURE_PLATEAU_13] = Texture_creer("assets/images/plateau_13.png");
	registreTextures[TEXTURE_PLATEAU_19] = Texture_creer("assets/images/plateau_19.png");
	registreTextures[TEXTURE_AURA] = Texture_creer("assets/images/aura.png");
	registreTextures[TEXTURE_BACKGROUND] = Texture_creer("assets/images/background.jpg");

	status = 1;

	for(i = 0; i < NB_TEXTURES; i++)
	{
		if(registreTextures[i] == NULL)
		{
			fprintf(stdout, "Erreur de chargement de la texture %d.\n", i);
			status = 0;
		}
	}

	return status;
}

void Texture_libererRegistre()
{
	int i;

	for(i = 0; i < NB_TEXTURES; i++)
	{
		if(registreTextures[i] != NULL)
			Texture_detruire(registreTextures[i]);
	}
}
