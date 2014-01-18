/**
 * @file main.c
 * @brief Le jeu de Go c'est trop bien !
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <SDL/SDL.h>

#include "include/Liste.h"
#include "include/Position.h"
#include "include/modes/contextes/Contexte.h"
#include "include/modes/ecrans/Ecran.h"
#include "include/modes/ecrans/EcranJeu.h"

int main(int argc, char* argv[])
{
	FonctionMainEcran fctMain;

	if(!Contexte_initialiser(GRAPHIQUE))
	{
		fprintf(stderr, "Erreur d'initialisation du contexte graphique.\n");
		return 1;
	}

	Position_initGC();
	Liste_initGC();

	Ecran_setIDProchain(JEU);
	Ecran_changer();

	EcranJeu_init();

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
