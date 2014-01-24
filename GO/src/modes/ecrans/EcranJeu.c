/**
 * @file EcranJeu.c
 * @brief 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>

#include "include/Position.h"
#include "include/Plateau.h"
#include "include/Partie.h"
#include "include/Liste.h"
#include "include/Chaine.h"
#include "include/Chaines.h"

#include "include/modes/ecrans/Ecran.h"
#include "include/modes/ecrans/EcranJeu.h"
#include "include/modes/ecrans/EcranMenu.h"

#include "include/modes/contextes/Contexte.h"
#include "include/modes/interfaces/InterfaceGraphique.h"
#include "include/modes/interfaces/InterfaceConsole.h"

#include "include/modes/etats/EtatsJeu.h"

static EtatsJeu etats;

static int tourDeJeu(Position position)
{
	Pion pion;
	Chaines chaines;
	Chaine chaine;
	Couleur couleur;
	Plateau copiePlateau;
	int valide;

	copiePlateau = Plateau_copier(Partie_getPlateauActuel(etats.partie));
	couleur = Partie_getJoueurActuel(etats.partie);
	pion = Pion_creer(position, couleur);

	chaines = Plateau_capturerChaines(copiePlateau, pion, &valide);
	assert(chaines);

	if(valide)
	{
		if(!Liste_estVide(chaines))
		{
			Liste_tete(chaines);

			do
			{
				chaine = Liste_courant(chaines);
				Liste_supprimerCourant(chaines);

				Plateau_realiserCapture(copiePlateau, chaine);

				Chaine_vider(chaine);
				Chaine_detruire(chaine);
			} while(!Liste_estVide(chaines));
		}

		if(Partie_appartientPlateau(etats.partie, copiePlateau))
		{
			valide = 0;
		}
	}

	if(valide)
	{
		Partie_jouerTour(etats.partie);
		Partie_insererPlateau(etats.partie, copiePlateau);
	}
	else
		Plateau_detruire(copiePlateau);

	Liste_detruire(chaines);
	Pion_detruire(pion);

	return valide;
}

int EcranJeu_init(char* nomJ1, char* nomJ2, TypeJoueur typeJ1, TypeJoueur typeJ2, int taille, int handicap, float komi)
{
	etats.continuer = 1;
	etats.estFini = 0;
	etats.scoreNoir = 0;
	etats.scoreBlanc = 0;
	etats.partie = Partie_creer(nomJ1, nomJ2, typeJ1, typeJ2, komi, handicap, taille);
	etats.premiereBoucle = 1;
	etats.derniereBoucle = 0;

	if(etats.partie == NULL)
		return 0;

	return 1;
}

int EcranJeu_initCharger()
{
	FILE* fp = fopen("sauvegarde.dat", "rb");

	if(fp == NULL)
		return 0;

	etats.continuer = 1;
	etats.estFini = 0;
	etats.scoreNoir = 0;
	etats.scoreBlanc = 0;
	etats.partie = Partie_charger(fp);
	etats.derniereBoucle = 0;
	etats.premiereBoucle = 1;

	fclose(fp);

	if(etats.partie == NULL)
		return 0;

	return 1;
}

void EcranJeu_detruire()
{
	Partie_detruire(etats.partie);
}

void EcranJeu_main()
{
	FonctionEntreeEcran entreeFct = EcranJeu_getEntreeFct();
	FonctionSortieEcran sortieFct = EcranJeu_getSortieFct();
	Couleur couleur;
	Liste positions;
	int passeTour, valide, id;
	Position pos;

	srand(time(NULL));

	while(etats.continuer)
	{
		entreeFct(&etats);

		if(etats.estFini == 0 && Partie_estFinie(etats.partie))
		{
			etats.estFini = 1;
			Partie_calculerScore(etats.partie, &(etats.scoreNoir), &(etats.scoreBlanc));
		}

		couleur = Partie_getJoueurActuel(etats.partie);

		// Super IA de la mort !
		if(!etats.estFini && Partie_getTypeJoueur(etats.partie, couleur) == ORDINATEUR)
		{
			passeTour = 0;
			valide = 0;

			if(Partie_getToursPasses(etats.partie) == 1) // Si un joueur a passé un tour, l'autre a une chance sur 4 de passer aussi.
			{
				if(rand() % 4 == 0)
				{
					passeTour = 1;
					EcranJeu_eventPasserTour();
				}
			}

			if(!passeTour)
			{
				positions = Partie_getPositionsLibres(etats.partie);

				while(!Liste_estVide(positions) && !valide)
				{
					id = rand() % Liste_getNbElements(positions);
					Liste_setCourant(positions, id);
					pos = Liste_courant(positions);
					valide = EcranJeu_eventPlacerPion(Position_getX(pos), Position_getY(pos));

					if(!valide)
					{
						Position_detruire(pos);
						Liste_supprimerCourant(positions);
					}
				}

				if(!valide)
					EcranJeu_eventPasserTour();

				Liste_tete(positions);

				while(!Liste_estVide(positions))
				{
					Position_detruire(Liste_courant(positions));
					Liste_supprimerCourant(positions);
				}

				Liste_detruire(positions);
			}
		}

		sortieFct(&etats);
	}

	EcranJeu_detruire();
}

FonctionEntreeEcran EcranJeu_getEntreeFct()
{
	TypeContexte contexte = Contexte_getID();

	switch(contexte)
	{
		case GRAPHIQUE:
			return (FonctionEntreeEcran) InterfaceGraphique_entreeJeu;
		case CONSOLE:
			return (FonctionEntreeEcran) InterfaceConsole_entreeJeu;

		default:
			return NULL;
	}
}

FonctionSortieEcran EcranJeu_getSortieFct()
{
	TypeContexte contexte = Contexte_getID();

	switch(contexte)
	{
		case GRAPHIQUE:
			return (FonctionSortieEcran) InterfaceGraphique_sortieJeu;
		case CONSOLE:
			return (FonctionSortieEcran) InterfaceConsole_sortieJeu;

		default:
			return NULL;
	}
}

void EcranJeu_eventArreter(int menu)
{
	if(menu)
	{
		Ecran_setIDProchain(MENU);
		EcranMenu_init();
	}
	else
		Ecran_setIDProchain(NONE);

	etats.continuer = 0;
}

int EcranJeu_eventPlacerPion(int cx, int cy)
{
	int valide;

	if(Partie_estFinie(etats.partie))
		return 0;

	if(!Partie_estAuDernier(etats.partie))
		Partie_supprimerPlateauxSuivants(etats.partie);

	etats.estFini = 0;

	Position position = Position_creer(cx, cy);

	if(Plateau_get(Partie_getPlateauActuel(etats.partie), position) == VIDE)
	{
		valide = tourDeJeu(position);
	}

	Position_detruire(position);

	return valide;
}

void EcranJeu_eventPasserTour()
{
	if(Partie_estFinie(etats.partie))
		return;

	if(!Partie_estAuDernier(etats.partie))
		Partie_supprimerPlateauxSuivants(etats.partie);

	etats.estFini = 0;

	Partie_insererPlateau(etats.partie, Plateau_copier(Partie_getPlateauActuel(etats.partie)));
	Partie_passerTour(etats.partie);
}

void EcranJeu_eventSauvegarder()
{
	FILE* fp = fopen("sauvegarde.dat", "wb");

	if(!fp)
		return;

	Partie_sauvegarder(etats.partie, fp);

	fclose(fp);
}

void EcranJeu_eventSuivant()
{
	if(Partie_estAuDernier(etats.partie))
		return;

	Partie_avancer(etats.partie);
}

void EcranJeu_eventPrecedent()
{
	if(Partie_estAuPremier(etats.partie))
		return;

	Partie_rembobiner(etats.partie);
}
