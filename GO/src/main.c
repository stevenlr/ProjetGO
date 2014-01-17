/**
 * @file main.c
 * @brief Le jeu de Go c'est trop bien !
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <SDL/SDL.h>

#include "include/modes/contextes/Contexte.h"
#include "include/modes/contextes/ContexteGraphique.h"

#include "include/Texture.h"
#include "include/Plateau.h"
#include "include/Chaine.h"

#define TAILLE_CELL 30

void tourDeJeu(Plateau plateau, Couleur couleur, Position position)
{
	Pion pion;
	Chaines chaines;
	Chaine chaine;
	int valide;

	pion = Pion_creer(position, couleur);

	chaines = Plateau_capturerChaines(plateau, pion, &valide);
	assert(chaines);

	if(!valide)
	{
		Plateau_set(plateau, position, VIDE);
	}
	else if(!Liste_estVide(chaines))
	{
		Liste_tete(chaines);

		do
		{
			chaine = Liste_courant(chaines);
			Liste_supprimerCourant(chaines);

			Plateau_realiserCapture(plateau, chaine);

			Chaine_vider(chaine);
			Chaine_detruire(chaine);
		} while(!Liste_estVide(chaines));
	}

	Liste_detruire(chaines);
	Pion_detruire(pion);
}

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
	int i, j;
	int cx, cy;

	if(!Contexte_initialiser(GRAPHIQUE))
	{
		fprintf(stderr, "Erreur d'initialisation du contexte graphique.\n");
		return 1;
	}

	Position_initGC();
	Liste_initGC();

	window = ContexteGraphique_getWindow();

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

					if(Plateau_get(plateau, position) == VIDE)
					{
						couleur = (event.button.button == SDL_BUTTON_LEFT) ? BLANC : NOIR;
						tourDeJeu(plateau, couleur, position);
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

	Contexte_detruire();

	Position_nettoyerGC();
	Liste_nettoyerGC();

	return 0;
}
