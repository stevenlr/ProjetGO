/**
 * @file main.c
 * @brief Le jeu de Go c'est trop bien !
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>


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

	while(continuer)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				continuer = 0;
		}

		SDL_Delay(10);
	}

	SDL_Quit();

	return 0;
}
