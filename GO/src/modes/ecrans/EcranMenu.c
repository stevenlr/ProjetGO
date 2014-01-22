/**
 * @file EcranMenu.c
 * @brief 
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "include/Liste.h"

#include "include/modes/ecrans/Ecran.h"
#include "include/modes/ecrans/EcranMenu.h"
#include "include/modes/ecrans/EcranJeu.h"

#include "include/modes/contextes/Contexte.h"
#include "include/modes/interfaces/InterfaceGraphique.h"
#include "include/modes/interfaces/InterfaceConsole.h"

#include "include/modes/etats/EtatsMenu.h"

static EtatsMenu etats;

void EcranMenu_init()
{
	etats.continuer = 1;
	etats.premiereBoucle = 1;
	etats.derniereBoucle = 0;
}

void EcranMenu_detruire()
{

}

void EcranMenu_main()
{
	FonctionEntreeEcran entreeFct = EcranMenu_getEntreeFct();
	FonctionSortieEcran sortieFct = EcranMenu_getSortieFct();

	while(etats.continuer)
	{
		entreeFct(&etats);

		sortieFct(&etats);
	}

	EcranMenu_detruire();
}

FonctionEntreeEcran EcranMenu_getEntreeFct()
{
	TypeContexte contexte = Contexte_getID();

	switch(contexte)
	{
		case GRAPHIQUE:
			return (FonctionEntreeEcran) InterfaceGraphique_entreeMenu;
		case CONSOLE:
			return (FonctionEntreeEcran) InterfaceConsole_entreeMenu;
		default:
			return NULL;
	}
}

FonctionSortieEcran EcranMenu_getSortieFct()
{
	TypeContexte contexte = Contexte_getID();

	switch(contexte)
	{
		case GRAPHIQUE:
			return (FonctionSortieEcran) InterfaceGraphique_sortieMenu;
		case CONSOLE:
			return (FonctionEntreeEcran) InterfaceConsole_sortieMenu;
		default:
			return NULL;
	}
}

void EcranMenu_eventQuitter()
{
	etats.continuer = 0;
	Ecran_setIDProchain(NONE);
}

void EcranMenu_eventReprendre()
{
	if(!EcranJeu_initCharger())
		return;

	etats.continuer = 0;
	Ecran_setIDProchain(JEU);
}

void EcranMenu_eventNouvellePartie()
{
	/**
	 * @todo changer pour configurer partie
	 */
	EcranJeu_init();

	etats.continuer = 0;
	Ecran_setIDProchain(JEU);
}

void EcranMenu_eventGuide()
{
	if(!EcranGuide_init())
		return;

	etats.continuer = 0;
	Ecran_setIDProchain(GUIDE);
}
