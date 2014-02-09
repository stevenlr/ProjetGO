/**
 * @file EcranGuide.c
 * @brief 
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "include/Liste.h"
#include "include/Tutoriel.h"

#include "include/modes/ecrans/Ecran.h"
#include "include/modes/ecrans/EcranMenu.h"
#include "include/modes/ecrans/EcranGuide.h"

#include "include/modes/contextes/Contexte.h"
#include "include/modes/interfaces/InterfaceGraphique.h"
#include "include/modes/interfaces/InterfaceConsole.h"

#include "include/modes/etats/EtatsGuide.h"

static EtatsGuide etats;

int EcranGuide_init()
{
	int maxCaracteres;
	TypeContexte contexte = Contexte_getID();

	etats.continuer = 1;
	etats.besoinRafraichir = 1;
	etats.premiereBoucle = 1;
	etats.derniereBoucle = 0;

	maxCaracteres = (contexte == GRAPHIQUE) ? 100 : 78;
	etats.tutoriel = Tutoriel_charger(maxCaracteres);

	if(etats.tutoriel == NULL)
		return 0;

	Tutoriel_tete(etats.tutoriel);

	return 1;
}

void EcranGuide_detruire()
{
	Tutoriel_detruire(etats.tutoriel);
}

void EcranGuide_main()
{
	FonctionEntreeEcran entreeFct = EcranGuide_getEntreeFct();
	FonctionSortieEcran sortieFct = EcranGuide_getSortieFct();

	while(etats.continuer)
	{
		entreeFct(&etats);

		sortieFct(&etats);
	}

	EcranGuide_detruire();
}

FonctionEntreeEcran EcranGuide_getEntreeFct()
{
	TypeContexte contexte = Contexte_getID();

	switch(contexte)
	{
		case GRAPHIQUE:
			return (FonctionEntreeEcran) InterfaceGraphique_entreeGuide;
		case CONSOLE:
			return (FonctionEntreeEcran) InterfaceConsole_entreeGuide;
		default:
			return NULL;
	}
}

FonctionSortieEcran EcranGuide_getSortieFct()
{
	TypeContexte contexte = Contexte_getID();

	switch(contexte)
	{
		case GRAPHIQUE:
			return (FonctionSortieEcran) InterfaceGraphique_sortieGuide;
		case CONSOLE:
			return (FonctionEntreeEcran) InterfaceConsole_sortieGuide;
		default:
			return NULL;
	}
}

void EcranGuide_eventQuitter(int menu)
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

void EcranGuide_eventPrecedent()
{
	if(!Tutoriel_estPremier(etats.tutoriel))
		Tutoriel_precedent(etats.tutoriel);

	etats.besoinRafraichir = 1;
}

void EcranGuide_eventSuivant()
{
	if(!Tutoriel_estDernier(etats.tutoriel))
		Tutoriel_suivant(etats.tutoriel);

	etats.besoinRafraichir = 1;
}
