/**
 * @file main.c
 * @brief Le jeu de Go c'est trop bien !
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "include/Tutoriel.h"

#include "include/Liste.h"
#include "include/Position.h"
#include "include/modes/contextes/Contexte.h"
#include "include/modes/ecrans/Ecran.h"
#include "include/modes/ecrans/EcranMenu.h"

int main(int argc, char* argv[])
{
	FonctionMainEcran fctMain;

	if(!Contexte_initialiser(GRAPHIQUE))
	{
		fprintf(stderr, "Erreur d'initialisation du contexte.\n");
		return 1;
	}

	Position_initGC();
	Liste_initGC();

	Ecran_setIDProchain(MENU);
	Ecran_changer();

	EcranMenu_init();

	Tutoriel_convertirTexteVersBinaire();

	do
	{
		fctMain = Ecran_getFonctionMain();
		fctMain();

		Ecran_changer();
	} while(Ecran_getID() != NONE);

	Contexte_detruire();

	Position_nettoyerGC();
	Liste_nettoyerGC();

	return 0;
}
