/**
 * @file EcranOptions.c
 * @brief 
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "include/modes/ecrans/Ecran.h"
#include "include/modes/ecrans/EcranJeu.h"
#include "include/modes/ecrans/EcranMenu.h"
#include "include/modes/ecrans/EcranOptions.h"

#include "include/modes/contextes/Contexte.h"
#include "include/modes/interfaces/InterfaceGraphique.h"
#include "include/modes/interfaces/InterfaceConsole.h"

#include "include/modes/etats/EtatsOptions.h"

EtatsOptions etats;

void EcranOptions_init()
{
	etats.continuer = 1;

	memset(etats.nomJ1, 0, 17);
	memset(etats.nomJ2, 0, 17);

	strcpy(etats.nomJ1, "Nom joueur 1");
	strcpy(etats.nomJ2, "Nom joueur 2");

	etats.typeJ1 = HUMAIN;
	etats.typeJ2 = HUMAIN;

	etats.handicap = 0;
	etats.komi = 7;
	etats.taille = 19;

	etats.joueurHandicap = BLANC;
	etats.premiereBoucle = 1;
}

void EcranOptions_detruire()
{

}

void EcranOptions_main()
{
	FonctionEntreeEcran entreeFct = EcranOptions_getEntreeFct();
	FonctionSortieEcran sortieFct = EcranOptions_getSortieFct();

	while(etats.continuer)
	{
		entreeFct(&etats);

		sortieFct(&etats);
	}

	EcranOptions_detruire();
}

FonctionEntreeEcran EcranOptions_getEntreeFct()
{
	TypeContexte contexte = Contexte_getID();

	switch(contexte)
	{
		case GRAPHIQUE:
			return (FonctionEntreeEcran) InterfaceGraphique_entreeOptions;
		case CONSOLE:
			/**
			 * @todo ce truc là
			 */
			//return (FonctionEntreeEcran) InterfaceConsole_entreeOptions;
		default:
			return NULL;
	}
}

FonctionSortieEcran EcranOptions_getSortieFct()
{
	TypeContexte contexte = Contexte_getID();

	switch(contexte)
	{
		case GRAPHIQUE:
			return (FonctionSortieEcran) InterfaceGraphique_sortieOptions;
		case CONSOLE:
			/**
			 * @todo ça aussi
			 */
			//return (FonctionSortieEcran) InterfaceConsole_sortieOptions;

		default:
			return NULL;
	}
}

void EcranOptions_eventQuitter(int menu)
{
	etats.continuer = 0;

	if(menu)
	{
		EcranMenu_init();
		Ecran_setIDProchain(MENU);
		return;
	}

	Ecran_setIDProchain(NONE);
}

void EcranOptions_eventSetKomi(int komi)
{
	if(komi < 0) komi = 0;
	else if(komi > 99) komi = 99;

	etats.komi = komi;
}

void EcranOptions_eventSetHandicap(int handicap)
{
	if(handicap < 0) handicap = 0;
	else if(handicap > 64) handicap = 64;

	etats.handicap = handicap;
}

void EcranOptions_eventSetTypeJoueur(Couleur joueur, TypeJoueur type)
{
	if(joueur == NOIR)
		etats.typeJ1 = type;
	else
		etats.typeJ2 = type;
}

void EcranOptions_eventSetNomJoueur(Couleur joueur, char* nom)
{
	if(joueur == NOIR)
		strcpy(etats.nomJ1, nom);
	else
		strcpy(etats.nomJ2, nom);
}

void EcranOptions_eventSetJoueurHandicap(Couleur joueur)
{
	etats.joueurHandicap = joueur;
}

void EcranOptions_eventSetTaille(int taille)
{
	if(taille != 9 && taille != 13 && taille != 19)
		return;

	etats.taille = taille;
}

void EcranOptions_eventCommencer()
{
	int handicap;

	handicap = (etats.joueurHandicap == NOIR) ? -etats.handicap : etats.handicap;

	if(!EcranJeu_init(etats.nomJ1, etats.nomJ2, etats.typeJ1, etats.typeJ2, etats.taille, handicap, etats.komi + 0.5))
		return;

	etats.continuer = 0;
	Ecran_setIDProchain(JEU);
}
