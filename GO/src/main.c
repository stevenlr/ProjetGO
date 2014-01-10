/**
 * @file main.c
 * @brief Le jeu de Go c'est trop bien !
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "include/Texture.h"

int main(int argc, char* argv[])
{
	SDL_Surface* window;
	SDL_Event event;
	int continuer = 1;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Erreur d'initialisation SDL.\n");
		return 1;
	}

	SDL_WM_SetCaption("Jeu de Go", NULL);

	window = SDL_SetVideoMode(1280, 720, 24, SDL_HWSURFACE);
	if(window == NULL)
	{
		fprintf(stderr, "Erreur de creation de la fenetre.\n");
		return 1;
	}
	printf("b");
	if(!Texture_chargerRegistre())
	{
		printf("a");
		Texture_libererRegistre();
		SDL_Quit();
		return 1;
	}

	while(continuer)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				continuer = 0;
		}

		Texture_blit(TEXTURE_PLATEAU_13, window, 10, 10);
		Texture_blit(TEXTURE_PION_BLANC, window, 40, 70);
		Texture_blit(TEXTURE_PION_NOIR, window, 70, 100);

		SDL_Flip(window);
		SDL_Delay(10);
	}

	Texture_libererRegistre();
	SDL_Quit();

	return 0;
}
