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
	int tour;
	int passe;
	char* joueurNoir;
	char* joueurBlanc;
	TypeJoueur typeJoueurNoir;
	TypeJoueur typeJoueurBlanc;
};

Partie Partie_creer(char* joueurNoir, char* joueurBlanc, TypeJoueur typeNoir, TypeJoueur typeBlanc, float komi, int handicap, int taille)
{
	Partie partie;
	Plateau plateau;

	partie = malloc(sizeof(struct Partie));

	if(partie == NULL)
		return NULL;

	partie->joueurNoir = malloc(sizeof(strlen(joueurNoir)));
	partie->joueurBlanc = malloc(sizeof(strlen(joueurBlanc)));
	partie->typeJoueurNoir = typeNoir;
	partie->typeJoueurBlanc = typeBlanc;

	if(partie->joueurNoir == NULL || partie->joueurBlanc == NULL)
		return NULL;

	strcpy(partie->joueurNoir, joueurNoir);
	strcpy(partie->joueurBlanc, joueurBlanc);

	plateau = Plateau_creer(taille);
	partie->plateaux = Liste_creer();
	Partie_insererPlateau(partie, plateau);

	partie->komi = komi;
	partie->handicap = handicap;
	partie->tour = 0;
	partie->taille = taille;
	partie->passe = 0;

	return partie;
}

static void Partie_viderPlateaux(Liste plateaux)
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

int Partie_getTour(Partie partie)
{
	return partie->tour;
}

char* Partie_getJoueur(Partie partie, Couleur couleur)
{
	if(couleur == NOIR)
		return partie->joueurNoir;

	return partie->joueurBlanc;
}

Couleur Partie_getJoueurActuel(Partie partie)
{
	int nhandicap = (partie->handicap < 0) ? -(partie->handicap) : partie->handicap;
	int mod = (partie->tour - nhandicap) % 2;

	if(partie->tour < nhandicap)
	{
		return (partie->handicap < 0) ? BLANC : NOIR;
	}

	if(partie->handicap > 0)
	{
		return (mod == 0) ? BLANC : NOIR;
	}

	return (mod == 0) ? NOIR : BLANC;
}

Plateau Partie_getPlateauActuel(Partie partie)
{
	Liste_queue(partie->plateaux);
	return Liste_courant(partie->plateaux);
}

int Partie_appartientPlateau(Partie partie, Plateau plateau)
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
	*scoreNoir = (partie->handicap < 0) ? partie->komi : 0;
	*scoreBlanc = (partie->handicap >= 0) ? partie->komi : 0;
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

void Partie_passerTour(Partie partie)
{
	partie->tour++;
	partie->passe++;
}

void Partie_jouerTour(Partie partie)
{
	partie->tour++;
	partie->passe = 0;
}

int Partie_estFinie(Partie partie)
{
	return partie->passe == 2;
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
	fwrite(&(partie->tour), sizeof(int), 1, fichier);
	fwrite(&(partie->passe), sizeof(int), 1, fichier);
	fwrite(&tailleBlanc, sizeof(int), 1, fichier);
	fwrite(&tailleNoir, sizeof(int), 1, fichier);
	fwrite(partie->joueurBlanc, sizeof(char), tailleBlanc, fichier);
	fwrite(partie->joueurNoir, sizeof(char), tailleNoir, fichier);
	fwrite(&(partie->typeJoueurBlanc), sizeof(TypeJoueur), 1, fichier);
	fwrite(&(partie->typeJoueurNoir), sizeof(TypeJoueur), 1, fichier);

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
	int handicap, taille, tailleBlanc, tailleNoir, tour, passe;
	float komi;
	char* joueurBlanc;
	char* joueurNoir;
	Plateau plateau;
	TypeJoueur typeBlanc, typeNoir;

	fread(&handicap, sizeof(int), 1, fichier);
	fread(&komi, sizeof(float), 1, fichier);
	fread(&taille, sizeof(int), 1, fichier);
	fread(&tour, sizeof(int), 1, fichier);
	fread(&passe, sizeof(int), 1, fichier);

	fread(&tailleBlanc, sizeof(int), 1, fichier);
	fread(&tailleNoir, sizeof(int), 1, fichier);

	joueurBlanc = malloc(sizeof(char) * tailleBlanc);
	joueurNoir = malloc(sizeof(char) * tailleNoir);
	fread(joueurBlanc, sizeof(char), tailleBlanc, fichier);
	fread(joueurNoir, sizeof(char), tailleNoir, fichier);
	fread(&typeBlanc, sizeof(TypeJoueur), 1, fichier);
	fread(&typeNoir, sizeof(TypeJoueur), 1, fichier);

	if(ferror(fichier))			// S'il y a une erreur maintenant, il ne peut creer une partie via Partie_creer.
	{
		free(joueurBlanc);
		free(joueurNoir);
		return NULL;
	}

	partie = Partie_creer(joueurNoir, joueurBlanc, typeBlanc, typeNoir, komi, handicap, taille);
	partie->tour = tour;
	partie->passe = passe;

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
