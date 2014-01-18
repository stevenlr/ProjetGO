/**
 * @file InterfaceGraphique.c
 * @brief 
 */

#include <SDL/SDL.h>

#include "include/Texture.h"
#include "include/Position.h"
#include "include/Plateau.h"
#include "include/Couleur.h"

#include "include/modes/interfaces/InterfaceGraphique.h"
#include "include/modes/contextes/ContexteGraphique.h"
#include "include/modes/ecrans/EcranJeu.h"

void InterfaceGraphique_entreeJeu(EtatsJeu* etats)
{
	SDL_Event event;
	int cx, cy;
	int originePlateau;
	int taillePlateau;

	taillePlateau = etats->taillePlateau;
	originePlateau = (ContexteGraphique_getTailleY() - taillePlateau * TAILLE_CELL) / 2;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			EcranJeu_eventArreter();
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			cx = (event.button.x - originePlateau) / TAILLE_CELL;
			cy = (event.button.y - originePlateau) / TAILLE_CELL;

			if(cx >= 0 && cx < taillePlateau && cy >= 0 && cy < taillePlateau)
			{
				EcranJeu_eventPlacerPion(cx, cy);
			}
		}
	}
}

void InterfaceGraphique_sortieJeu(EtatsJeu* etats)
{
	SDL_Surface* window;
	int tailleX, tailleY, i, j, originePlateau;
	SDL_Rect rect;
	Position position;
	Couleur couleur;
	IdTexture texture;

	window = ContexteGraphique_getWindow();
	tailleX = ContexteGraphique_getTailleX();
	tailleY = ContexteGraphique_getTailleY();

	originePlateau = (ContexteGraphique_getTailleY() - etats->taillePlateau * TAILLE_CELL) / 2;

	rect.x = 0;
	rect.y = 0;
	rect.w = tailleX;
	rect.h = tailleY;

	SDL_FillRect(window, &rect, 0x000000);

	position = Position_creer(0, 0);

	switch(etats->taillePlateau)
	{
		case 9:
			texture = TEXTURE_PLATEAU_9;
			break;
		case 13:
			texture = TEXTURE_PLATEAU_13;
			break;
		case 19:
			texture = TEXTURE_PLATEAU_19;
			break;
		default:
			texture = TEXTURE_PLATEAU_19;
			break;
	}

	Texture_blitCentre(texture, window, tailleY / 2, tailleY / 2);

	for(i = 0; i < etats->taillePlateau; i++)
	{
		for(j = 0; j < etats->taillePlateau; j++)
		{
			Position_setX(position, j);
			Position_setY(position, i);

			couleur = Plateau_get(etats->plateau, position);

			if(couleur == NOIR)
				Texture_blit(TEXTURE_PION_NOIR, window, j * TAILLE_CELL + originePlateau, i * TAILLE_CELL + originePlateau);
			else if(couleur == BLANC)
				Texture_blit(TEXTURE_PION_BLANC, window, j * TAILLE_CELL + originePlateau, i * TAILLE_CELL + originePlateau);
		}
	}

	Position_detruire(position);
	SDL_Flip(window);
	SDL_Delay(10); // Doucement le matin, pas trop vite l'après-midi.
}
