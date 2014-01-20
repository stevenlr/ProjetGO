/**
 * @file EcranJeu.c
 * @brief 
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "include/Position.h"
#include "include/Plateau.h"
#include "include/Partie.h"
#include "include/Liste.h"
#include "include/Chaine.h"
#include "include/Chaines.h"

#include "include/modes/ecrans/Ecran.h"
#include "include/modes/ecrans/EcranJeu.h"

#include "include/modes/contextes/Contexte.h"
#include "include/modes/interfaces/InterfaceGraphique.h"

#include "include/modes/etats/EtatsJeu.h"

static EtatsJeu etats;

static void tourDeJeu(Position position)
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
}

void EcranJeu_init()
{
	FILE* fp = fopen("sauvegarde.dat", "rb");

	etats.continuer = 1;
	etats.estFini = 0;
	etats.scoreNoir = 0;
	etats.scoreBlanc = 0;
	etats.partie = Partie_creer("Joueur 1", "Joueur 2", HUMAIN, HUMAIN, 7.5, 0, 19);
	//etats.partie = Partie_charger(fp);

	fclose(fp);
}

void EcranJeu_detruire()
{
	Partie_detruire(etats.partie);
}

void EcranJeu_main()
{
	FonctionEntreeEcran entreeFct = EcranJeu_getEntreeFct();
	FonctionSortieEcran sortieFct = EcranJeu_getSortieFct();

	while(etats.continuer)
	{
		entreeFct(&etats);

		if(etats.estFini == 0 && Partie_estFinie(etats.partie))
		{
			etats.estFini = 1;
			Partie_calculerScore(etats.partie, &(etats.scoreNoir), &(etats.scoreBlanc));
		}

		sortieFct(&etats);
	}

	EcranJeu_detruire();
	Ecran_setIDProchain(NONE);
}

FonctionEntreeEcran EcranJeu_getEntreeFct()
{
	TypeContexte contexte = Contexte_getID();

	switch(contexte)
	{
		case GRAPHIQUE:
			return (FonctionEntreeEcran) InterfaceGraphique_entreeJeu;
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
		default:
			return NULL;
	}
}

void EcranJeu_eventArreter()
{
	etats.continuer = 0;
}

void EcranJeu_eventPlacerPion(int cx, int cy)
{
	if(Partie_estFinie(etats.partie))
			return;

	Position position = Position_creer(cx, cy);

	if(Plateau_get(Partie_getPlateauActuel(etats.partie), position) == VIDE)
	{
		tourDeJeu(position);
	}

	Position_detruire(position);
}

void EcranJeu_eventPasserTour()
{
	if(Partie_estFinie(etats.partie))
		return;

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
