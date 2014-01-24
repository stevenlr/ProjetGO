/**
 * @file Partie.c
 * @brief Fonctions de Partie
 */

#include <stdio.h>
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
	int plateauCourant;
};

Partie Partie_creer(char* joueurNoir, char* joueurBlanc, TypeJoueur typeNoir, TypeJoueur typeBlanc, float komi, int handicap, int taille)
{
	Partie partie;
	Plateau plateau;
	int tailleJ1, tailleJ2;

	tailleJ1 = strlen(joueurNoir);
	tailleJ2 = strlen(joueurBlanc);

	partie = malloc(sizeof(struct Partie));

	if(partie == NULL)
		return NULL;

	partie->joueurNoir = malloc(sizeof(char) * (tailleJ1+ 2));
	partie->joueurBlanc = malloc(sizeof(char) * (tailleJ2 + 2));
	partie->typeJoueurNoir = typeNoir;
	partie->typeJoueurBlanc = typeBlanc;

	if(partie->joueurNoir == NULL || partie->joueurBlanc == NULL)
	{
		free(partie);
		return NULL;
	}

	strncpy(partie->joueurNoir, joueurNoir, tailleJ1);
	strncpy(partie->joueurBlanc, joueurBlanc, tailleJ2);

	partie->joueurNoir[tailleJ1] = '\0';
	partie->joueurBlanc[tailleJ2] = '\0';

	plateau = Plateau_creer(taille);
	partie->plateaux = Liste_creer();
	Partie_insererPlateau(partie, plateau);

	partie->komi = komi;
	partie->handicap = handicap;
	partie->tour = 0;
	partie->taille = taille;
	partie->passe = 0;
	partie->plateauCourant = 0;

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

int Partie_getToursPasses(Partie partie)
{
	return partie->passe;
}

Liste Partie_getPositionsLibres(Partie partie)
{
	Liste positions = Liste_creer();
	Position pos = Position_creer(0, 0);
	int x, y, taille;
	Couleur couleur;
	Plateau plateau = Partie_getPlateauActuel(partie);

	taille = partie->taille;

	for(y = 0; y < taille; y++)
	{
		Position_setY(pos, y);

		for(x = 0; x < taille; x++)
		{
			Position_setX(pos, x);
			couleur = Plateau_get(plateau, pos);

			if(couleur == VIDE)
				Liste_insererCourant(positions, Position_copier(pos));
		}
	}

	Position_detruire(pos);

	return positions;
}

char* Partie_getJoueur(Partie partie, Couleur couleur)
{
	if(couleur == NOIR)
		return partie->joueurNoir;

	return partie->joueurBlanc;
}

TypeJoueur Partie_getTypeJoueur(Partie partie, Couleur couleur)
{
	return (Partie_getJoueurActuel(partie) == NOIR) ? partie->typeJoueurNoir : partie->typeJoueurBlanc;
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
	Liste_setCourant(partie->plateaux, partie->plateauCourant);
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
	Liste_insererQueue(partie->plateaux, plateau);
	partie->plateauCourant++;
}

void Partie_calculerScore(Partie partie, float* scoreNoir, float* scoreBlanc)
{
	int i, j, taille;
	Territoire territoire;
	Position position;
	Plateau plateau;
	Plateau dejaTraite;

	plateau = Partie_getPlateauActuel(partie);
	dejaTraite = Plateau_creer(Plateau_getTaille(plateau));

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

			if(Plateau_get(dejaTraite, position) != VIDE)
				continue;

			if(Plateau_get(plateau, position) == NOIR)
			{
				*scoreNoir += 1;
				Plateau_set(dejaTraite, position, NOIR);
				continue;
			}

			if(Plateau_get(plateau, position) == BLANC)
			{
				*scoreBlanc += 1;
				Plateau_set(dejaTraite, position, NOIR);
				continue;
			}

			if((territoire = Territoire_determinerTerritoire(plateau, position)) != NULL)
			{
				if(Chaine_getCouleur(territoire) != VIDE)
				{
					if(Chaine_getCouleur(territoire) == BLANC)
						*scoreBlanc += Territoire_determinerNbCases(territoire);
					else
						*scoreNoir += Territoire_determinerNbCases(territoire);
				}

				Chaine_tete(territoire);

				do
				{
					Plateau_set(dejaTraite, Chaine_courant(territoire), NOIR);
				} while(Chaine_suivant(territoire));

				Chaine_vider(territoire);
				Chaine_detruire(territoire);
			}
		}
	}

	Plateau_detruire(dejaTraite);
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
	return partie->passe >= 2;
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

	return ferror(fichier) != 0;
}

Partie Partie_charger(FILE* fichier)
{
	Partie partie;
	int handicap, taille, tailleBlanc, tailleNoir, tour, passe;
	long tailleFichier;
	float komi;
	char* joueurBlanc;
	char* joueurNoir;
	Plateau plateau;
	TypeJoueur typeBlanc, typeNoir;

	fseek(fichier, 0, SEEK_END);
	tailleFichier = ftell(fichier);
	fseek(fichier, 0, SEEK_SET);

	fread(&handicap, sizeof(int), 1, fichier);
	fread(&komi, sizeof(float), 1, fichier);
	fread(&taille, sizeof(int), 1, fichier);
	fread(&tour, sizeof(int), 1, fichier);
	fread(&passe, sizeof(int), 1, fichier);
	fread(&tailleBlanc, sizeof(int), 1, fichier);
	fread(&tailleNoir, sizeof(int), 1, fichier);
	joueurBlanc = malloc(sizeof(char) * (tailleBlanc + 1));
	joueurNoir = malloc(sizeof(char) * (tailleNoir + 1));
	fread(joueurBlanc, sizeof(char), tailleBlanc, fichier);
	fread(joueurNoir, sizeof(char), tailleNoir, fichier);
	fread(&typeBlanc, sizeof(TypeJoueur), 1, fichier);
	fread(&typeNoir, sizeof(TypeJoueur), 1, fichier);

	joueurBlanc[tailleBlanc] = '\0';
	joueurNoir[tailleNoir] = '\0';

	if(ferror(fichier))
	{
		free(joueurBlanc);
		free(joueurNoir);
		return NULL;
	}

	partie = Partie_creer(joueurNoir, joueurBlanc, typeBlanc, typeNoir, komi, handicap, taille);

	if(partie == NULL)
		return NULL;

	partie->tour = tour;
	partie->passe = passe;

	free(joueurBlanc);
	free(joueurNoir);


	while(ftell(fichier) != tailleFichier)
	{
		plateau = Plateau_charger(fichier);
		Partie_insererPlateau(partie, plateau);
	}

	if(ferror(fichier))
		return NULL;

	return partie;
}

int Partie_estAuPremier(Partie partie)
{
	return partie->plateauCourant == 0;
}

int Partie_estAuDernier(Partie partie)
{
	return partie->plateauCourant == (Liste_getNbElements(partie->plateaux) - 1);
}

void Partie_rembobiner(Partie partie)
{
	partie->plateauCourant--;
	partie->tour--;

	if(partie->passe > 0)
		partie->passe--;
}

void Partie_avancer(Partie partie)
{
	partie->plateauCourant++;
	partie->tour++;
}

void Partie_supprimerPlateauxSuivants(Partie partie)
{
	Plateau plateau, courant;

	Liste_setCourant(partie->plateaux, partie->plateauCourant);
	courant = Liste_courant(partie->plateaux);

	if(!Liste_suivant(partie->plateaux))
		return;

	while(Liste_courant(partie->plateaux) != courant)
	{
		plateau = Liste_courant(partie->plateaux);
		Plateau_detruire(plateau);
		Liste_supprimerCourant(partie->plateaux);
	}
}
