/**
 * @file Texture.h
 * @brief 
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#define NB_TEXTURES 6

typedef struct Texture* Texture;

typedef enum {
	TEXTURE_PION_BLANC,
	TEXTURE_PION_NOIR,
	TEXTURE_PLATEAU_9,
	TEXTURE_PLATEAU_13,
	TEXTURE_PLATEAU_19,
	TEXTURE_AURA
} IdTexture;

/**
 * Colle une texture sur une surface SDL.
 *
 * @param idTexture id de la texture � coller.
 * @param surface Surface sur laquelle coller.
 * @param x Position x o� coller la texture.
 * @param y Position y o� coller la texture.
 */
void Texture_blit(IdTexture idTexture, SDL_Surface* surface, int x, int y);

/**
 * Colle une texture sur une surface SDL centr� sur le point donn�.
 *
 * @param idTexture id de la texture � coller.
 * @param surface Surface sur laquelle coller.
 * @param x Position x o� coller la texture.
 * @param y Position y o� coller la texture.
 */
void Texture_blitCentre(IdTexture idTexture, SDL_Surface* surface, int centreX, int centreY);

/**
 * Charge toutes les textures dans le registre.
 *
 * @return 0 en cas d'erreur, 1 sinon.
 */
int Texture_chargerRegistre();

/**
 * D�truit toutes les textures pr�sentes dans le registre.
 */
void Texture_libererRegistre();

#endif
