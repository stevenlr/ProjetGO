/**
 * @file InterfaceGraphique.c
 * @brief 
 */

#include <SDL/SDL.h>

#include "include/Position.h"
#include "include/Partie.h"
#include "include/Plateau.h"
#include "include/Couleur.h"

#include "include/graphics/Bouton.h"
#include "include/graphics/Texture.h"
#include "include/graphics/Texte.h"

#include "include/modes/interfaces/InterfaceGraphique.h"
#include "include/modes/contextes/ContexteGraphique.h"
#include "include/modes/ecrans/EcranJeu.h"

void InterfaceGraphique_entreeJeu(EtatsJeu* etats)
{
	SDL_Event event;
	int cx, cy, x, y;
	int originePlateau;
	int taillePlateau;

	taillePlateau = Partie_getTaille(etats->partie);
	originePlateau = (ContexteGraphique_getTailleY() - taillePlateau * TAILLE_CELL) / 2;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			EcranJeu_eventArreter();
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			x = event.button.x;
			y = event.button.y;
			cx = (x - originePlateau) / TAILLE_CELL;
			cy = (y - originePlateau) / TAILLE_CELL;

			if(cx >= 0 && cx < taillePlateau && cy >= 0 && cy < taillePlateau)
			{
				EcranJeu_eventPlacerPion(cx, cy);
			}
			else if(Bouton_clique(&(boutons[JEU_PASSER]), x, y))
			{
				EcranJeu_eventPasserTour();
			}
			else if(Bouton_clique(&(boutons[JEU_SAUVEGARDER]), x, y))
			{
				EcranJeu_eventSauvegarder();
			}
			else if(Bouton_clique(&(boutons[JEU_QUITTER]), x, y))
			{
				EcranJeu_eventArreter();
			}
		}
	}
}

void InterfaceGraphique_sortieJeu(EtatsJeu* etats)
{
	SDL_Surface* window;
	int tailleX, tailleY, i, j, originePlateau, taillePlateau;
	int bordDroit, bordGauche, milieu, couleurInt;
	SDL_Rect rect;
	Position position;
	Couleur couleur, tour;
	IdTexture texture;
	char str[32];

	taillePlateau = Partie_getTaille(etats->partie);
	tour = Partie_getJoueurActuel(etats->partie);
	window = ContexteGraphique_getWindow();
	tailleX = ContexteGraphique_getTailleX();
	tailleY = ContexteGraphique_getTailleY();

	bordGauche = tailleY;
	bordDroit = tailleX - 15;
	milieu = bordGauche + (bordDroit - bordGauche) / 2;

	originePlateau = (ContexteGraphique_getTailleY() - taillePlateau * TAILLE_CELL) / 2;

	rect.x = 0;
	rect.y = 0;
	rect.w = tailleX;
	rect.h = tailleY;

	SDL_FillRect(window, &rect, 0x000000);

	position = Position_creer(0, 0);

	switch(taillePlateau)
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

	for(i = 0; i < taillePlateau; i++)
	{
		for(j = 0; j < taillePlateau; j++)
		{
			Position_setX(position, j);
			Position_setY(position, i);

			couleur = Plateau_get(Partie_getPlateauActuel(etats->partie), position);

			if(couleur == NOIR)
				Texture_blit(TEXTURE_PION_NOIR, window, j * TAILLE_CELL + originePlateau, i * TAILLE_CELL + originePlateau);
			else if(couleur == BLANC)
				Texture_blit(TEXTURE_PION_BLANC, window, j * TAILLE_CELL + originePlateau, i * TAILLE_CELL + originePlateau);
		}
	}

	Texte_afficherChaine(window, milieu, 15, "Jeu de Go", GRAS | GRAND, 0xffffff, CENTRE_X);

	sprintf(str, "Tour %d", Partie_getTour(etats->partie) + 1);
	Texte_afficherChaine(window, milieu, 100, str, GRAND, 0xaaaaaa, CENTRE_X);

	Texture_blit(TEXTURE_PION_NOIR, window, bordGauche, 157);
	couleurInt = (tour == NOIR) ? 0xffffff : 0x707070;
	Texte_afficherChaine(window, bordGauche + 40, 160, Partie_getJoueur(etats->partie, NOIR), NORMAL, couleurInt, GAUCHE);

	Texture_blit(TEXTURE_PION_BLANC, window, bordGauche, 197);
	couleurInt = (tour == NOIR) ? 0x707070 : 0xffffff;
	Texte_afficherChaine(window, bordGauche + 40, 200, Partie_getJoueur(etats->partie, BLANC), NORMAL, couleurInt, GAUCHE);

	if(Partie_estFinie(etats->partie))
	{
		Texte_afficherChaine(window, milieu, 330, "Partie terminée", GRAS | GRAND, 0xffff00, CENTRE_X);

		sprintf(str, "Noir : %.1f - Blanc : %.1f", etats->scoreNoir, etats->scoreBlanc);
		Texte_afficherChaine(window, milieu, 380, str, NORMAL, 0xaaaaaa, CENTRE_X);

		if(etats->scoreNoir > etats->scoreBlanc)
			couleur = NOIR;
		else
			couleur = BLANC;

		sprintf(str, "%s remporte la partie", Partie_getJoueur(etats->partie, couleur));
		Texte_afficherChaine(window, milieu, 410, str, NORMAL, 0xdddddd, CENTRE_X);
	}

	Bouton_afficher(&(boutons[JEU_PASSER]), window);
	Bouton_afficher(&(boutons[JEU_QUITTER]), window);
	Bouton_afficher(&(boutons[JEU_SAUVEGARDER]), window);

	Position_detruire(position);
	SDL_Flip(window);
	SDL_Delay(25); // Doucement le matin, pas trop vite l'après-midi.
}
