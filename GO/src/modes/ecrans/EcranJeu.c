/**
 * @file EcranJeu.c
 * @brief 
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "include/Position.h"
#include "include/Plateau.h"
#include "include/Liste.h"
#include "include/Chaine.h"
#include "include/Chaines.h"

#include "include/modes/ecrans/Ecran.h"
#include "include/modes/ecrans/EcranJeu.h"

#include "include/modes/contextes/Contexte.h"
#include "include/modes/interfaces/InterfaceGraphique.h"

#include "include/modes/etats/EtatsJeu.h"

static EtatsJeu etats;

static void tourDeJeu(Couleur couleur, Position position)
{
	Pion pion;
	Chaines chaines;
	Chaine chaine;
	int valide;

	pion = Pion_creer(position, couleur);

	chaines = Plateau_capturerChaines(etats.plateau, pion, &valide);
	assert(chaines);

	if(!valide)
	{
		Plateau_set(etats.plateau, position, VIDE);
	}
	else if(!Liste_estVide(chaines))
	{
		Liste_tete(chaines);

		do
		{
			chaine = Liste_courant(chaines);
			Liste_supprimerCourant(chaines);

			Plateau_realiserCapture(etats.plateau, chaine);

			Chaine_vider(chaine);
			Chaine_detruire(chaine);
		} while(!Liste_estVide(chaines));
	}

	if(valide)
		etats.tour++;

	Liste_detruire(chaines);
	Pion_detruire(pion);
}

void EcranJeu_init()
{
	etats.tour = 0;
	etats.taillePlateau = 19;
	etats.continuer = 1;
	etats.plateau = Plateau_creer(etats.taillePlateau);
}

void EcranJeu_detruire()
{
	Plateau_detruire(etats.plateau);
}

void EcranJeu_main()
{
	FonctionEntreeEcran entreeFct = EcranJeu_getEntreeFct();
	FonctionSortieEcran sortieFct = EcranJeu_getSortieFct();

	while(etats.continuer)
	{
		entreeFct(&etats);
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
	Position position = Position_creer(cx, cy);
	Couleur couleur;

	if(Plateau_get(etats.plateau, position) == VIDE)
	{
		couleur = (etats.tour % 2 == 0) ? NOIR : BLANC;
		tourDeJeu(couleur, position);
	}

	Position_detruire(position);
}
