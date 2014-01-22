/**
 * @file InterfaceGraphique.c
 * @brief
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/Position.h"
#include "include/Partie.h"
#include "include/Plateau.h"
#include "include/Couleur.h"

#include "include/modes/interfaces/InterfaceConsole.h"
#include "include/modes/ecrans/EcranJeu.h"
#include "include/modes/ecrans/EcranMenu.h"

static void InterfaceConsole_viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void InterfaceConsole_entreeJeu(EtatsJeu* etats)
{
	int cx, cy;
	int taillePlateau;
	char event[12];

	if(etats->premiereBoucle)
	{
		etats->premiereBoucle = 0;
		return;
	}

	taillePlateau = Partie_getTaille(etats->partie);

	do
	{
		scanf("%11s", event);
		InterfaceConsole_viderBuffer();		//Utile ? Habitude que j'ai pris donc bon

		if(strlen(event) < 4 && strlen(event) > 1)
		{
			if(event[0] >= 'A' && event[0] < 'A' + taillePlateau && event[1] > '0' && event[1] <= '9')
			{
				cx = (int) (event[0] - 'A');

				if(event[1] == '1' && strlen(event) == 3)
					cy = 10 + (int)(event[2] - '0');
				else
					cy = (int) (event[1] - '1');

				if(cx >= 0 && cx < taillePlateau && cy >= 0 && cy < taillePlateau)
						{
							EcranJeu_eventPlacerPion(cx, cy);
						}
				break;
			}
		}
		else if(strcmp(event, "quitter") == 0)
		{
			EcranJeu_eventArreter(1);
			break;
		}
		else if(strcmp(event, "passer") == 0)
		{
			EcranJeu_eventPasserTour();
			break;
		}
		else if(strcmp(event, "sauvegarder") == 0)
		{
			EcranJeu_eventSauvegarder();
			break;
		}
		else if(strcmp(event, "suivant") == 0)
		{
			EcranJeu_eventSuivant();
			break;
		}
		else if(strcmp(event, "precedent") == 0)
		{
			EcranJeu_eventPrecedent();
			break;
		}
	}while(1);
}

void InterfaceConsole_sortieJeu(EtatsJeu* etats)
{
	int i, j, taillePlateau;
	Position position;
	Couleur couleur, tour;
	char* str;

	taillePlateau = Partie_getTaille(etats->partie);
	tour = Partie_getJoueurActuel(etats->partie);

	position = Position_creer(0, 0);

	for(i = 0; i < taillePlateau; i++)
	{
		for(j = 0; j < taillePlateau; j++)
		{
			Position_setX(position, j);
			Position_setY(position, i);

			couleur = Plateau_get(Partie_getPlateauActuel(etats->partie), position);

			if(couleur == NOIR)
			{
				/**
				 * @todo Affichage du goban
				 */
			}
			else if(couleur == BLANC)
			{
				/**
				 * @todo Affichage du goban
				 */
			}
		}
	}

	printf("Commandes : quitter, sauvegarder, passer");

	if(!Partie_estAuPremier(etats->partie))
		{
		printf(" ,precedent");
		}

	if(!Partie_estAuDernier(etats->partie))
		{
		printf(" ,suivant");
		}

	printf(".\nPour jouer : [LETTRE][NOMBRE]. Ex : A2, F13.\n");

	if(etats->estFini)
	{
		str = malloc(sizeof(char) * 6);

		if(etats->scoreNoir > etats->scoreBlanc)
			strcpy(str, "Noir");
		else
			strcpy(str, "Blanc");

		printf("Partie terminée au tour %d !\n", Partie_getTour(etats->partie) + 1);
		printf("Score Noir : %.1f\t Score Blanc : %.1f\n", etats->scoreNoir, etats->scoreBlanc);
		printf("%s a gagné !\nQue souhaitez vous faire : ", str);

		free(str);
	}
	else
	{
		str = malloc(sizeof(char) * 6);

		if(tour == NOIR)
			strcpy(str, "Noir");
		else
			strcpy(str, "Blanc");

		printf("Tour n%d : C'est à %s de jouer ! Votre choix est : ", Partie_getTour(etats->partie) + 1, str);

		free(str);
	}

	Position_detruire(position);
}


void InterfaceConsole_entreeMenu(EtatsMenu* etats)
{
	int event;

	if(etats->premiereBoucle)
	{
		etats->premiereBoucle = 0;
		return;
	}

	do
	{
		scanf("%d", &event);
		InterfaceConsole_viderBuffer();		//Utile ? Habitude que j'ai pris donc bon

		switch(event)
		{
		case 1:
			EcranMenu_eventNouvellePartie();
			break;
		case 2:
			EcranMenu_eventReprendre();
			break;
		case 3:
			// Tutoriel
			break;
		case 4:
			EcranMenu_eventQuitter();
			break;
		}
	}while(event < 1 || event > 4);

	etats->derniereBoucle = 1;	//Tel que c'est codé, dans tous les cas ce sera la dernière. Sinon il aura fallu enlevé le while précédent.
}

void InterfaceConsole_sortieMenu(EtatsMenu* etats)
{
	if(etats->derniereBoucle)
	{
		etats->derniereBoucle = 0;
		return;
	}

	printf("****************************\n*\tJeu de GO\t*\n****************************\n");

	printf("Menu :\n");
	printf("\t1. Nouvelle Partie\n");
	printf("\t2. Reprendre une partie\n");
	printf("\t3. Tutoriel\n");
	printf("\t4. Quitter\n");

	printf("Votre choix est : ");
}
