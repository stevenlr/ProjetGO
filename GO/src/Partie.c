/**
 * @file Partie.c
 * @brief Fonctions de Partie
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "include/Partie.h"
#include "include/Liste.h"
#include "include/Territoire.h"

struct Partie
{
	Liste plateaux;
	Couleur joueurActuel;
	float komi;
	int taille;
	int handicap;		//< +X = Noir a X coup au départ. -X = Blanc a X coup au départ. 0 = sans handicap. (A voir si on gère ça là ou pas)
	char* joueurNoir;	//< Noir
	char* joueurBlanc;	//< Blanc
};

Partie Partie_creer(char* joueurNoir, char* joueurBlanc, float komi, int handicap, int taille)
{
	Partie partie;
	Plateau plateau;

	partie = malloc(sizeof(struct Partie));

	if(partie == NULL)
		return NULL;

	partie->joueurNoir = malloc(sizeof(strlen(joueurNoir)));
	partie->joueurBlanc = malloc(sizeof(strlen(joueurBlanc)));

	if(partie->joueurNoir == NULL || partie->joueurBlanc == NULL)
		return NULL;

	strcpy(partie->joueurNoir, joueurNoir);
	strcpy(partie->joueurNoir, joueurNoir);

	plateau = Plateau_creer(taille);
	partie->plateaux = Liste_creer();
	Partie_insererPlateau(partie, plateau);

	partie->komi = komi;
	partie->handicap = handicap;
	partie->taille = taille;

	if(handicap < 0)
		partie->joueurActuel = BLANC;
	else
		partie->joueurActuel = NOIR;

	return partie;
}

static void Partie_viderPlateaux(Liste plateaux)	// Oui Mr. Gautier a eu la flemme de faire un fichier Plateaux.h/.c pour UNE fonction x)
{
	Plateau plateau;

	assert(plateaux);

	if(Liste_estVide(plateaux))
		return;

	Liste_tete(plateaux);

	do
	{
		plateau = Liste_courant(plateaux);
		assert(plateau);
		Plateau_detruire(plateau);

		Liste_supprimerCourant(plateaux);
	} while(!Liste_estVide(plateaux));
}

void Partie_detruire(Partie partie)
{
	free(partie->joueurNoir);
	free(partie->joueurBlanc);

	Partie_viderPlateaux(partie->plateaux);
	Liste_detruire(partie->plateaux);

	free(partie);
}

int Partie_getHandicap(Partie partie)
{
	return partie->handicap;
}

float Partie_getKomi(Partie partie)
{
	return partie->komi;
}

int Partie_getTaille(Partie partie)
{
	return partie->taille;
}

void Partie_getJoueur(Partie partie, Couleur couleur, char* joueur)
{
	if(couleur == NOIR)
		strcpy(joueur, partie->joueurNoir);
	else
		strcpy(joueur, partie->joueurBlanc);
}

Couleur Partie_getJoueurActuel(Partie partie)
{
	return partie->joueurActuel;
}

void Partie_changeJoueurActuel(Partie partie)
{
	if(partie->handicap == 0)
	{
		if(partie->joueurActuel == NOIR)
			partie->joueurActuel = BLANC;
		else
			partie->joueurActuel = NOIR;
		return;
	}

	if(partie->handicap > 0)
		partie->handicap--;
	else
		partie->handicap++;
}

Plateau Partie_getPlateauActuel(Partie partie)
{
	Liste_queue(partie->plateaux);
	return Liste_courant(partie->plateaux);
}

static int Partie_appartientPlateau(Partie partie, Plateau plateau)
{
	Plateau plateauCourant;

	if(Liste_estVide(partie->plateaux))
		return 0;

	Liste_queue(partie->plateaux);	// Parcours inversé car il y a + de chances de trouver rapidement que plateau == plateauPrec

	do
	{
		plateauCourant = Liste_courant(partie->plateaux);

		if(Plateau_estIdentique(plateau, plateauCourant))
			return 1;

	} while(Liste_precedent(partie->plateaux));

	return 0;
}

void Partie_insererPlateau(Partie partie, Plateau plateau)
{
	if(!Partie_appartientPlateau(partie, plateau))
	{
		Liste_insererQueue(partie->plateaux, plateau);
	}
}

void Plateau_calculerScore(Partie partie, float* scoreNoir, float* scoreBlanc)
{
	int i, j, taille;
	Territoire territoire;
	Position position;
	Plateau plateau;

	plateau = Partie_getPlateauActuel(partie);

	taille = Plateau_getTaille(plateau);
	*scoreNoir = 0;
	*scoreBlanc = Partie_getKomi(partie);
	position = Position_creer(0, 0);

	for(i = 0; i < taille; i++)
	{
		Position_setX(position, i);

		for(j = 0; j < taille; j++)
		{
			Position_setY(position, j);

			if(Plateau_get(plateau, position) == NOIR)
				*scoreNoir += 1;
			else if(Plateau_get(plateau, position) == BLANC)
				*scoreBlanc += 1;


			if((territoire = Territoire_determinerTerritoire(plateau, position)) != NULL)
			{
				if(Chaine_getCouleur(territoire) != VIDE)
				{
					if(Chaine_getCouleur(territoire) == BLANC)
						*scoreBlanc += Territoire_determinerNbCases(territoire);
					else
						*scoreNoir += Territoire_determinerNbCases(territoire);
				}

				Chaine_vider(territoire);
				Chaine_detruire(territoire);
			}
		}
	}

	Position_detruire(position);
}

int Partie_sauvegarder(Partie partie, FILE* fichier)
{
	Plateau plateau;
	int tailleBlanc, tailleNoir;

	tailleBlanc = strlen(partie->joueurBlanc);
	tailleNoir = strlen(partie->joueurNoir);

	fwrite(&(partie->handicap), sizeof(int), 1, fichier);
	fwrite(&(partie->komi), sizeof(float), 1, fichier);
	fwrite(&(partie->taille), sizeof(int), 1, fichier);
	fwrite(&(partie->joueurActuel), sizeof(Couleur), 1, fichier);
	fwrite(&tailleBlanc, sizeof(int), 1, fichier);
	fwrite(&tailleNoir, sizeof(int), 1, fichier);
	fwrite(partie->joueurBlanc, sizeof(char), tailleBlanc, fichier);
	fwrite(partie->joueurNoir, sizeof(char), tailleNoir, fichier);

	Liste_tete(partie->plateaux);

	if(!Liste_suivant(partie->plateaux))	// Plateau_creer insere déjà le plateau vide ! Pas besoin de le stocker. (cf Partie_charger)
		return !ferror(fichier);

	do
	{
		plateau = Liste_courant(partie->plateaux);

		Plateau_sauvegarder(plateau, fichier);
	} while(Liste_suivant(partie->plateaux));

	return !ferror(fichier);				// Check s'il y a eu une erreur de writing
}

Partie Partie_charger(FILE* fichier)
{
	Partie partie;
	int handicap, taille, tailleBlanc, tailleNoir;
	float komi;
	Couleur joueurActuel;
	char* joueurBlanc;
	char* joueurNoir;
	Plateau plateau;

	fread(&handicap, sizeof(int), 1, fichier);
	fread(&komi, sizeof(float), 1, fichier);
	fread(&taille, sizeof(int), 1, fichier);
	fread(&joueurActuel, sizeof(Couleur), 1, fichier);
	fread(&tailleBlanc, sizeof(int), 1, fichier);
	fread(&tailleNoir, sizeof(int), 1, fichier);

	joueurBlanc = malloc(sizeof(char) * tailleBlanc);
	joueurNoir = malloc(sizeof(char) * tailleNoir);
	fread(joueurBlanc, sizeof(char), tailleBlanc, fichier);
	fread(joueurNoir, sizeof(char), tailleNoir, fichier);

	if(ferror(fichier))			// S'il y a une erreur maintenant, il ne peut creer une partie via Partie_creer.
	{
		free(joueurBlanc);
		free(joueurNoir);
		return NULL;
	}

	partie = Partie_creer(joueurNoir, joueurBlanc, komi, handicap, taille);

	free(joueurBlanc);
	free(joueurNoir);

	while(!feof(fichier))		// Jusqu'à ce qu'on atteint la fin du fichier
	{
		plateau = Plateau_charger(fichier);
		Partie_insererPlateau(partie, plateau);
	}

	if(ferror(fichier))			// Check s'il y a eu une erreur de reading
		return NULL;

	return partie;
}
