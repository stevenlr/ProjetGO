/**
 * @file InterfaceGraphique.c
 * @brief
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "include/Position.h"
#include "include/Partie.h"
#include "include/Plateau.h"
#include "include/Couleur.h"

#include "include/modes/interfaces/InterfaceConsole.h"
#include "include/modes/ecrans/EcranJeu.h"
#include "include/modes/ecrans/EcranMenu.h"
#include "include/modes/ecrans/EcranGuide.h"

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
		InterfaceConsole_viderBuffer();

		if(strlen(event) < 4 && strlen(event) > 1)
		{
			if(event[0] >= 'A' && event[0] < 'A' + taillePlateau && event[1] > '0' && event[1] <= '9')
			{
				cx = (int) (event[0] - 'A');

				if(event[1] == '1' && strlen(event) == 3)
					cy = 9 + (int)(event[2] - '0');
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
			etats->derniereBoucle = 1;
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
		else
		{
			printf("Entrez un choix valide : ");
		}
	}while(1);
}

static int InterfaceConsole_estHoshi(int i, int j, int taillePlateau)
{
	if((i == 3 || i == 9 || i ==15) && (j == 3 || j == 9 || j == 15) && taillePlateau == 19)
	{
		return 1;
	}
	else if((i == 3 || i == 6 || i == 9) && (j == 3 || j == 6 || j == 9) && taillePlateau == 13)
	{
		return 1;
	}
	else if((i == 2 || i == 6) && (j == 2 || j == 6) && taillePlateau == 9)
	{
		return 1;
	}

	return 0;
}

void InterfaceConsole_sortieJeu(EtatsJeu* etats)
{
	int i, j, taillePlateau;
	Position position;
	Couleur couleur, tour;
	char* str;

	if(etats->derniereBoucle)
	{
		etats->derniereBoucle = 0;
		return;
	}

	taillePlateau = Partie_getTaille(etats->partie);
	tour = Partie_getJoueurActuel(etats->partie);

	position = Position_creer(0, 0);

	printf(" ");

	for(i=1; i <= taillePlateau; i++)
		{
			if(i < 10)
				printf(" %d ", i);
			else
				printf(" %d", i);
		}

	printf("\n");

	for(i = 0; i < taillePlateau; i++)
	{
		printf("%c", 'A' + i);

		for(j = 0; j < taillePlateau; j++)
		{
			Position_setX(position, i);
			Position_setY(position, j);

			couleur = Plateau_get(Partie_getPlateauActuel(etats->partie), position);

			if(couleur == VIDE)
			{
				if(InterfaceConsole_estHoshi(i, j, taillePlateau))
					printf(" %c ", (char) 197);
				else
					printf(" . ");
			}
			else
				printf(" %c ", Couleur_versChar(couleur));
		}

		printf("%c\n", 'A' + i);
	}

	printf(" ");

	for(i=1; i <= taillePlateau; i++)
	{
		if(i < 10)
			printf(" %d ", i);
		else
			printf(" %d", i);
	}

	printf("\nCommandes : quitter, sauvegarder, passer");

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

		printf("Partie terminee au tour %d !\n", Partie_getTour(etats->partie) + 1);
		printf("Score Noir : %.1f\t Score Blanc : %.1f\n", etats->scoreNoir, etats->scoreBlanc);
		printf("%s a gagne !\nQue souhaitez vous faire : ", str);

		free(str);
	}
	else
	{
		str = malloc(sizeof(char) * 6);

		if(tour == NOIR)
			strcpy(str, "Noir");
		else
			strcpy(str, "Blanc");

		printf("Tour n %d : C'est a %s de jouer ! Votre choix est : ", Partie_getTour(etats->partie) + 1, str);

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
		InterfaceConsole_viderBuffer();

		switch(event)
		{
		case 1:
			EcranMenu_eventNouvellePartie();
			break;
		case 2:
			EcranMenu_eventReprendre();
			break;
		case 3:
			EcranMenu_eventGuide();
			break;
		case 4:
			EcranMenu_eventQuitter();
			break;
		default:
			printf("Entrez un choix valide : ");
		}
	}while(event < 1 || event > 4);

	etats->derniereBoucle = 1;
}

void InterfaceConsole_sortieMenu(EtatsMenu* etats)
{
	if(etats->derniereBoucle)
	{
		etats->derniereBoucle = 0;
		return;
	}

	printf("*************************\n*\tJeu de GO\t*\n*************************\n");

	printf("Menu :\n");
	printf("\t1. Nouvelle Partie\n");
	printf("\t2. Reprendre une partie\n");
	printf("\t3. Tutoriel\n");
	printf("\t4. Quitter\n");

	printf("Votre choix est : ");
}

void InterfaceConsole_entreeGuide(EtatsGuide* etats)
{
	char event[12];

	if(etats->premiereBoucle)
	{
		etats->premiereBoucle = 0;
		return;
	}

	do
	{
		scanf("%11s", event);
		InterfaceConsole_viderBuffer();

		if(strcmp(event, "quitter") == 0)
		{
			EcranGuide_eventQuitter(1);
			etats->derniereBoucle = 1;
			break;
		}
		else if(strcmp(event, "suivant") == 0)
		{
			EcranGuide_eventSuivant();
			break;
		}
		else if(strcmp(event, "precedent") == 0)
		{
			EcranGuide_eventPrecedent();
			break;
		}
		else
		{
			printf("Entrez un choix valide : ");
		}
	}while(1);
}

void InterfaceConsole_sortieGuide(EtatsGuide* etats)
{
	int i, j;
	Liste chaines;
	Plateau plateau;
	Position pos;
	Couleur couleur;

	if(etats->derniereBoucle)
	{
		etats->derniereBoucle = 0;
		return;
	}

	pos = Position_creer(0, 0);

	Tutoriel_courant(etats->tutoriel, &plateau, &chaines);

	for(i=1; i <= 9; i++)
		{
			if(i < 10)
				printf(" %d ", i);
			else
				printf(" %d", i);
		}

	printf("\n");

	for(i = 0; i < 9; i++)
	{
		printf("%c", 'A' + i);

		for(j = 0; j < 9; j++)
		{
			Position_setX(pos, i);
			Position_setY(pos, j);

			couleur = Plateau_get(plateau, pos);

			if(couleur == VIDE)
			{
				if(InterfaceConsole_estHoshi(i, j, 9))
					printf(" %c ", (char) 197);
				else
					printf(" . ");
			}
			else if(couleur == AURAVIDE)
			{
				if(InterfaceConsole_estHoshi(i, j, 9))
				{
					//textcolor(4);
					printf(" %c ",(char) 197);
					//textcolor(15);
				}
				else
					printf("   ");
			}
			else
			{
				if(couleur == AURABLANC)
					printf(" %c ", Couleur_versChar(couleur));
				else if(couleur == AURANOIR)
					printf(" %c ", Couleur_versChar(couleur));
				else
					printf(" %c ", Couleur_versChar(couleur));
			}
		}

		printf("%c\n", 'A' + i);
	}

	printf(" ");

	for(i=1; i <= 9; i++)
	{
		if(i < 10)
			printf(" %d ", i);
		else
			printf(" %d", i);
	}

	printf("\n");

	i = 0;
	Liste_tete(chaines);

	do
	{
		printf("%s\n", (char *) Liste_courant(chaines));
	} while(Liste_suivant(chaines));

	printf("( Commande : quitter");

	if(!Tutoriel_estPremier(etats->tutoriel))
		printf(", precedent");

	if(!Tutoriel_estDernier(etats->tutoriel))
		printf(", suivant");

	printf(". ) Votre choix est : ");

	Position_detruire(pos);



}
