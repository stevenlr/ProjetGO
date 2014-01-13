/**
 * @file main.c
 * @brief Le jeu de Go c'est trop bien !
 */

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "include/Texture.h"
#include "include/Plateau.h"

#define TAILLE_CELL 30

int main(int argc, char* argv[])
{
	SDL_Surface* window;
	SDL_Event event;
	int continuer = 1;
	int taillePlateau = 19;
	int originePlateau;
	Plateau plateau;
	Position position;
	Couleur couleur;
	SDL_Rect rect;
	int i, j, couleurAPoser = 0;
	int cx, cy;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Erreur d'initialisation SDL.\n");
		return 1;
	}

	SDL_WM_SetCaption("Jeu de Go", NULL);

	window = SDL_SetVideoMode(1066, 600, 24, SDL_HWSURFACE);
	if(window == NULL)
	{
		fprintf(stderr, "Erreur de creation de la fenetre.\n");
		return 1;
	}

	if(!Texture_chargerRegistre())
	{
		Texture_libererRegistre();
		SDL_Quit();
		return 1;
	}

	position = Position_creer(0, 0);
	plateau = Plateau_creer(taillePlateau);
	originePlateau = (600 - taillePlateau * TAILLE_CELL) / 2;

	while(continuer)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				continuer = 0;
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				cx = (event.button.x - originePlateau) / TAILLE_CELL;
				cy = (event.button.y - originePlateau) / TAILLE_CELL;

				if(cx >= 0 && cx < taillePlateau && cy >= 0 && cy < taillePlateau)
				{
					Position_setX(position, cx);
					Position_setY(position, cy);

					if(event.button.button == SDL_BUTTON_LEFT && Plateau_get(plateau, position) == VIDE)
					{
						couleurAPoser = (couleurAPoser + 1) % 2;
						couleur = (couleurAPoser == 0) ? BLANC : NOIR;
						Plateau_set(plateau, position, couleur);
					}
					else if(event.button.button == SDL_BUTTON_RIGHT)
					{
						Plateau_set(plateau, position, VIDE);
					}
				}
			}
		}

		rect.x = 0;
		rect.y = 0;
		rect.w = 1066;
		rect.h = 600;

		SDL_FillRect(window, &rect, 0x000000);

		Texture_blitCentre(TEXTURE_PLATEAU_19, window, 300, 300);

		for(i = 0; i < taillePlateau; i++)
		{
			for(j = 0; j < taillePlateau; j++)
			{
				Position_setX(position, j);
				Position_setY(position, i);

				couleur = Plateau_get(plateau, position);

				if(couleur == NOIR)
					Texture_blit(TEXTURE_PION_NOIR, window, j * TAILLE_CELL + originePlateau, i * TAILLE_CELL + originePlateau);
				else if(couleur == BLANC)
					Texture_blit(TEXTURE_PION_BLANC, window, j * TAILLE_CELL + originePlateau, i * TAILLE_CELL + originePlateau);
			}
		}

		SDL_Flip(window);
		SDL_Delay(10);
	}

	Position_detruire(position);
	Plateau_detruire(plateau);
	Texture_libererRegistre();
	SDL_Quit();

	return 0;
}
