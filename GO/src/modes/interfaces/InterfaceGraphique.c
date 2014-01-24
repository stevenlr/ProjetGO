/**
 * @file InterfaceGraphique.c
 * @brief 
 */

#include <stdio.h>
#include <string.h>

#include <SDL/SDL.h>

#include "include/Position.h"
#include "include/Partie.h"
#include "include/Plateau.h"
#include "include/Couleur.h"

#include "include/graphics/ChoixMultiple.h"
#include "include/graphics/EntreeTexte.h"
#include "include/graphics/Bouton.h"
#include "include/graphics/Texture.h"
#include "include/graphics/Texte.h"

#include "include/modes/interfaces/InterfaceGraphique.h"
#include "include/modes/contextes/ContexteGraphique.h"

#include "include/modes/ecrans/EcranJeu.h"
#include "include/modes/ecrans/EcranMenu.h"
#include "include/modes/ecrans/EcranGuide.h"
#include "include/modes/ecrans/EcranOptions.h"

#include "include/modes/etats/EtatsJeu.h"
#include "include/modes/etats/EtatsMenu.h"
#include "include/modes/etats/EtatsGuide.h"
#include "include/modes/etats/EtatsOptions.h"

static void InterfaceGraphique_afficherPion(SDL_Surface* surface, Couleur couleur, int x, int y)
{
	if(couleur == AURANOIR || couleur == AURABLANC || couleur == AURAVIDE)
	{
		Texture_blit(TEXTURE_AURA, surface, x, y);

		if(couleur == AURAVIDE)
			return;

		couleur = (couleur == AURANOIR) ? NOIR : BLANC;
	}
	if(couleur == NOIR)
	{
		Texture_blit(TEXTURE_PION_NOIR, surface, x, y);
		return;
	}

	if(couleur == BLANC)
		Texture_blit(TEXTURE_PION_BLANC, surface, x, y);
}

void InterfaceGraphique_entreeJeu(EtatsJeu* etats)
{
	SDL_Event event;
	int cx, cy, x, y;
	int originePlateau;
	int taillePlateau;
	Couleur joueurActuel = Partie_getJoueurActuel(etats->partie);
	TypeJoueur typeJoueurActuel = Partie_getTypeJoueur(etats->partie, joueurActuel);

	taillePlateau = Partie_getTaille(etats->partie);
	originePlateau = (ContexteGraphique_getTailleY() - taillePlateau * TAILLE_CELL) / 2;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			EcranJeu_eventArreter(0);
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			x = event.button.x;
			y = event.button.y;
			cx = (x - originePlateau) / TAILLE_CELL;
			cy = (y - originePlateau) / TAILLE_CELL;

			if(cx >= 0 && cx < taillePlateau && cy >= 0 && cy < taillePlateau)
			{
				if(typeJoueurActuel == HUMAIN)
					EcranJeu_eventPlacerPion(cx, cy);
			}
			else if(Bouton_clique(boutons[JEU_PASSER], x, y))
			{
				if(typeJoueurActuel == HUMAIN)
					EcranJeu_eventPasserTour();
			}
			else if(Bouton_clique(boutons[JEU_SAUVEGARDER], x, y))
			{
				EcranJeu_eventSauvegarder();
			}
			else if(Bouton_clique(boutons[JEU_QUITTER], x, y))
			{
				EcranJeu_eventArreter(1);
			}
			else if(Bouton_clique(boutons[JEU_SUIVANT], x, y))
			{
				EcranJeu_eventSuivant();
			}
			else if(Bouton_clique(boutons[JEU_PRECEDENT], x, y))
			{
				EcranJeu_eventPrecedent();
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

			InterfaceGraphique_afficherPion(window, couleur, j * TAILLE_CELL + originePlateau, i * TAILLE_CELL + originePlateau);
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

	if(etats->estFini)
	{
		Texte_afficherChaine(window, milieu, 400, "Partie terminée", GRAS | GRAND, 0xffff00, CENTRE_X);

		sprintf(str, "Noir : %.1f - Blanc : %.1f", etats->scoreNoir, etats->scoreBlanc);
		Texte_afficherChaine(window, milieu, 450, str, NORMAL, 0xaaaaaa, CENTRE_X);

		if(etats->scoreNoir > etats->scoreBlanc)
			couleur = NOIR;
		else
			couleur = BLANC;

		sprintf(str, "%s remporte la partie", Partie_getJoueur(etats->partie, couleur));
		Texte_afficherChaine(window, milieu, 480, str, NORMAL, 0xdddddd, CENTRE_X);
	}

	Bouton_afficher(boutons[JEU_PASSER], window);
	Bouton_afficher(boutons[JEU_QUITTER], window);
	Bouton_afficher(boutons[JEU_SAUVEGARDER], window);

	if(!Partie_estAuPremier(etats->partie))
		Bouton_afficher(boutons[JEU_PRECEDENT], window);

	if(!Partie_estAuDernier(etats->partie))
		Bouton_afficher(boutons[JEU_SUIVANT], window);

	Position_detruire(position);
	SDL_Flip(window);
	SDL_Delay(25); // Doucement le matin, pas trop vite l'après-midi.
}

void InterfaceGraphique_entreeMenu(EtatsMenu* etats)
{
	SDL_Event event;
	int x, y;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			EcranMenu_eventQuitter();
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			x = event.button.x;
			y = event.button.y;

			if(Bouton_clique(boutons[MENU_QUITTER], x, y))
			{
				EcranMenu_eventQuitter();
			}
			else if(Bouton_clique(boutons[MENU_NOUVELLEPARTIE], x, y))
			{
				EcranMenu_eventNouvellePartie();
			}
			else if(Bouton_clique(boutons[MENU_REPRENDREPARTIE], x, y))
			{
				EcranMenu_eventReprendre();
			}
			else if(Bouton_clique(boutons[MENU_GUIDE], x, y))
			{
				EcranMenu_eventGuide();
			}
		}
	}
}

void InterfaceGraphique_sortieMenu(EtatsMenu* etats)
{
	SDL_Surface* window;
	int tailleX;

	window = ContexteGraphique_getWindow();
	tailleX = ContexteGraphique_getTailleX();

	Texture_blit(TEXTURE_BACKGROUND, window, 0, 0);

	Texte_afficherChaine(window, tailleX / 2, 50, "Jeu de Go", GRAS | GRAND, 0xffffff, CENTRE_X);

	Bouton_afficher(boutons[MENU_NOUVELLEPARTIE], window);
	Bouton_afficher(boutons[MENU_REPRENDREPARTIE], window);
	Bouton_afficher(boutons[MENU_GUIDE], window);
	Bouton_afficher(boutons[MENU_QUITTER], window);

	SDL_Flip(window);
	SDL_Delay(25);
}

void InterfaceGraphique_entreeGuide(EtatsGuide* etats)
{
	SDL_Event event;
	int x, y;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			EcranGuide_eventQuitter(0);
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			x = event.button.x;
			y = event.button.y;

			if(Bouton_clique(boutons[GUIDE_QUITTER], x, y))
			{
				EcranGuide_eventQuitter(1);
			}
			else if(Bouton_clique(boutons[GUIDE_PRECEDENT], x, y))
			{
				EcranGuide_eventPrecedent();
			}
			else if(Bouton_clique(boutons[GUIDE_SUIVANT], x, y))
			{
				EcranGuide_eventSuivant();
			}
		}
	}
}

void InterfaceGraphique_sortieGuide(EtatsGuide* etats)
{
	SDL_Surface* window;
	int tailleX, tailleY, originePlateauX, originePlateauY, origineTexte;
	int i, j;
	SDL_Rect rect;
	Liste chaines;
	Plateau plateau;
	Position pos;
	Couleur couleur;

	if(etats->besoinRafraichir)
	{
		window = ContexteGraphique_getWindow();
		tailleX = ContexteGraphique_getTailleX();
		tailleY = ContexteGraphique_getTailleY();

		pos = Position_creer(0, 0);

		originePlateauX = (tailleX - TAILLE_CELL * 9) / 2;
		originePlateauY = 80;

		origineTexte = originePlateauY + TAILLE_CELL * 9 + 50;

		rect.x = 0;
		rect.y = 0;
		rect.w = tailleX;
		rect.h = tailleY;

		SDL_FillRect(window, &rect, 0x000000);

		Bouton_afficher(boutons[GUIDE_QUITTER], window);

		if(!Tutoriel_estPremier(etats->tutoriel))
			Bouton_afficher(boutons[GUIDE_PRECEDENT], window);

		if(!Tutoriel_estDernier(etats->tutoriel))
			Bouton_afficher(boutons[GUIDE_SUIVANT], window);

		Texture_blit(TEXTURE_PLATEAU_9, window, originePlateauX, originePlateauY);

		Tutoriel_courant(etats->tutoriel, &plateau, &chaines);

		for(j = 0; j < 9; j++)
		{
			for(i = 0; i < 9; i++)
			{
				Position_setX(pos, i);
				Position_setY(pos, j);

				couleur = Plateau_get(plateau, pos);

				InterfaceGraphique_afficherPion(window, couleur, i * TAILLE_CELL + originePlateauX, j * TAILLE_CELL + originePlateauY);
			}
		}

		i = 0;
		Liste_tete(chaines);

		do
		{
			Texte_afficherChaine(window, 15, origineTexte + i * 25, Liste_courant(chaines), NORMAL, 0xffffff, GAUCHE);
			i++;
		} while(Liste_suivant(chaines));

		SDL_Flip(window);
		Position_detruire(pos);

		etats->besoinRafraichir = 0;
	}

	SDL_Delay(25);
}

void InterfaceGraphique_entreeOptions(EtatsOptions* etats)
{
	SDL_Event event;
	TypeJoueur type;
	EntreeTexte entree;
	int taille;
	Couleur joueur;
	int x, y;
	char c;

	if(etats->premiereBoucle)
	{
		ChoixMultiple_setCourant(choixMultiples[OPTIONS_TYPEJ1], 0);
		ChoixMultiple_setCourant(choixMultiples[OPTIONS_TYPEJ2], 0);
		ChoixMultiple_setCourant(choixMultiples[OPTIONS_TAILLE], 2);
		ChoixMultiple_setCourant(choixMultiples[OPTIONS_HANDICAP], 1);

		EntreeTexte_setTexte(entreesTexte[OPTIONS_NOMJ1], etats->nomJ1);
		EntreeTexte_setTexte(entreesTexte[OPTIONS_NOMJ2], etats->nomJ2);

		EntreeTexte_setFocus(entreesTexte[OPTIONS_NOMJ1], 0);
		EntreeTexte_setFocus(entreesTexte[OPTIONS_NOMJ2], 0);

		etats->premiereBoucle = 0;
	}

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
		{
			EcranOptions_eventQuitter(0);
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			x = event.button.x;
			y = event.button.y;

			EntreeTexte_setFocus(entreesTexte[OPTIONS_NOMJ1], 0);
			EntreeTexte_setFocus(entreesTexte[OPTIONS_NOMJ2], 0);

			EntreeTexte_clique(entreesTexte[OPTIONS_NOMJ1], x, y);
			EntreeTexte_clique(entreesTexte[OPTIONS_NOMJ2], x, y);

			if(Bouton_clique(boutons[OPTIONS_RETOUR], x, y))
			{
				EcranOptions_eventQuitter(1);
			}
			else if(Bouton_clique(boutons[OPTIONS_COMMENCER], x, y))
			{
				EcranOptions_eventSetNomJoueur(NOIR, EntreeTexte_getTexte(entreesTexte[OPTIONS_NOMJ1]));
				EcranOptions_eventSetNomJoueur(BLANC, EntreeTexte_getTexte(entreesTexte[OPTIONS_NOMJ2]));
				EcranOptions_eventCommencer();
			}
			else if(Bouton_clique(boutons[OPTIONS_KOMI_MOINS], x, y))
			{
				EcranOptions_eventSetKomi(etats->komi - 1);
			}
			else if(Bouton_clique(boutons[OPTIONS_KOMI_PLUS], x, y))
			{
				EcranOptions_eventSetKomi(etats->komi + 1);
			}
			else if(Bouton_clique(boutons[OPTIONS_HANDICAP_MOINS], x, y))
			{
				EcranOptions_eventSetHandicap(etats->handicap - 1);
			}
			else if(Bouton_clique(boutons[OPTIONS_HANDICAP_PLUS], x, y))
			{
				EcranOptions_eventSetHandicap(etats->handicap + 1);
			}
			else if(ChoixMultiple_clique(choixMultiples[OPTIONS_TYPEJ1], x, y))
			{
				type = (ChoixMultiple_getCourant(choixMultiples[OPTIONS_TYPEJ1]) == 0) ? HUMAIN : ORDINATEUR;
				EcranOptions_eventSetTypeJoueur(NOIR, type);
			}
			else if(ChoixMultiple_clique(choixMultiples[OPTIONS_TYPEJ2], x, y))
			{
				type = (ChoixMultiple_getCourant(choixMultiples[OPTIONS_TYPEJ2]) == 0) ? HUMAIN : ORDINATEUR;
				EcranOptions_eventSetTypeJoueur(BLANC, type);
			}
			else if(ChoixMultiple_clique(choixMultiples[OPTIONS_HANDICAP], x, y))
			{
				joueur = (ChoixMultiple_getCourant(choixMultiples[OPTIONS_HANDICAP]) == 0) ? NOIR : BLANC;
				EcranOptions_eventSetJoueurHandicap(joueur);
			}
			else if(ChoixMultiple_clique(choixMultiples[OPTIONS_TAILLE], x, y))
			{
				switch(ChoixMultiple_getCourant(choixMultiples[OPTIONS_TAILLE]))
				{
					case 0:
						taille = 9;
						break;
					case 1:
						taille = 13;
						break;
					case 2:
						taille = 19;
						break;
					default:
						taille = 19;
						break;
				}

				EcranOptions_eventSetTaille(taille);
			}
		}
		else if(event.type == SDL_KEYDOWN)
		{
			if(EntreeTexte_getFocus(entreesTexte[OPTIONS_NOMJ1]))
				entree = entreesTexte[OPTIONS_NOMJ1];
			else if(EntreeTexte_getFocus(entreesTexte[OPTIONS_NOMJ2]))
				entree = entreesTexte[OPTIONS_NOMJ2];
			else
				continue;

			if(event.key.keysym.sym == SDLK_BACKSPACE)
			{
				EntreeTexte_retour(entree);
			}
			else
			{
				c = (char) event.key.keysym.unicode;

				if((c == ' ' || c == '-' || c == '_')
						|| (c >= 'A' && c <= 'Z')
						|| (c >= 'a' && c <= 'z')
						|| (c >= '0' && c <=  '9'))
				{
					EntreeTexte_inserer(entree, c);
				}
			}

			EcranOptions_eventSetNomJoueur(NOIR, EntreeTexte_getTexte(entreesTexte[OPTIONS_NOMJ1]));
			EcranOptions_eventSetNomJoueur(BLANC, EntreeTexte_getTexte(entreesTexte[OPTIONS_NOMJ2]));
		}
	}
}

void InterfaceGraphique_sortieOptions(EtatsOptions* etats)
{
	SDL_Surface* window;
	SDL_Rect rect;
	int tailleX, tailleY;
	char str[100];

	window = ContexteGraphique_getWindow();
	tailleX = ContexteGraphique_getTailleX();
	tailleY = ContexteGraphique_getTailleY();

	rect.x = 0;
	rect.y = 0;
	rect.w = tailleX;
	rect.h = tailleY;

	SDL_FillRect(window, &rect, 0x000000);

	Bouton_afficher(boutons[OPTIONS_RETOUR], window);

	Texte_afficherChaine(window, 50, 130, "Joueur 1", NORMAL, 0xffffff, GAUCHE);
	EntreeTexte_afficher(entreesTexte[OPTIONS_NOMJ1], window);
	ChoixMultiple_afficher(choixMultiples[OPTIONS_TYPEJ1], window);

	Texte_afficherChaine(window, 50, 205, "Joueur 2", NORMAL, 0xffffff, GAUCHE);
	EntreeTexte_afficher(entreesTexte[OPTIONS_NOMJ2], window);
	ChoixMultiple_afficher(choixMultiples[OPTIONS_TYPEJ2], window);

	Texte_afficherChaine(window, 50, 280, "Taille du plateau", NORMAL, 0xffffff, GAUCHE);
	ChoixMultiple_afficher(choixMultiples[OPTIONS_TAILLE], window);

	Texte_afficherChaine(window, 50, 355, "Komi", NORMAL, 0xffffff, GAUCHE);
	Bouton_afficher(boutons[OPTIONS_KOMI_MOINS], window);
	Bouton_afficher(boutons[OPTIONS_KOMI_PLUS], window);
	sprintf(str, "%.1f", etats->komi + 0.5);
	Texte_afficherChaine(window, 400, 355, str, NORMAL, 0xffffff, CENTRE_X);

	Texte_afficherChaine(window, 50, 430, "Handicap", NORMAL, 0xffffff, GAUCHE);
	Bouton_afficher(boutons[OPTIONS_HANDICAP_MOINS], window);
	Bouton_afficher(boutons[OPTIONS_HANDICAP_PLUS], window);
	sprintf(str, "%d", etats->handicap);
	Texte_afficherChaine(window, 400, 430, str, NORMAL, 0xffffff, CENTRE_X);
	ChoixMultiple_afficher(choixMultiples[OPTIONS_HANDICAP], window);

	Bouton_afficher(boutons[OPTIONS_COMMENCER], window);

	SDL_Flip(window);
	SDL_Delay(25);
}
