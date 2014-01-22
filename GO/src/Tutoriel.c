/**
 * @file Tutoriel.c
 * @brief Fonctions du Tutoriel
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "include/Tutoriel.h"
#include "include/Liste.h"
#include "include/Partie.h"

struct Tutoriel
{
	Liste plateaux;
	Liste chaines;
};

int Tutoriel_convertirTexteVersBinaire()
{
	char c;
	char chaine[400];
	FILE *fichier, *fichier2;
	int n = 0, taille;

	fichier = fopen("assets/Tutoriel.txt", "r");
	fichier2 = fopen("assets/Tutoriel.bin", "wb");

	if(fichier == NULL || fichier2 == NULL)
		return 0;

	while((c = fgetc(fichier)) != EOF)
	{
		if(c != '\n')
			fwrite(&c, sizeof(char), 1, fichier2);
		else
		{
			n++;

			if(n % 9 == 0)
			{
				fgets(chaine, 400, fichier);

				taille = strlen(chaine) - 1;
				chaine[taille] = '\0';	//Censé enlever le \n

				fwrite(&taille, sizeof(int), 1, fichier2);		//Stocke la taille de la chaine
				fwrite(chaine, sizeof(char), taille, fichier2);	//Stocke la chaine de taille "taille".
			}
		}
	}

	return c == EOF || ferror(fichier2);
}

Tutoriel Tutoriel_charger(Partie partie, int nbCharParPhrase)
{
	Tutoriel tutoriel;
	Plateau plateau;
	char* chaine;
	char c;
	FILE* fichier;
	int tailleFichier, tailleChaine;
	Position pos;

	if((fichier = fopen("../assets/Tutoriel.bin", "rb")) == NULL)
		return NULL;

	fseek(fichier, 0, SEEK_END);
	tailleFichier = ftell(fichier);
	fseek(fichier, 0, SEEK_SET);

	tutoriel = Tutoriel_creer();
	plateau = Plateau_creer(9);
	pos = Position_creer(0, 0);

	while(ftell(fichier) != tailleFichier)
	{
		fread(&c, sizeof(char), 1, fichier);
		Plateau_set(plateau, pos, Couleur_charVersCouleur(c));

		if(Position_getX(pos) == 8)
		{
			Position_setX(pos, 0);

			if(Position_getY(pos) != 8)
				Position_setY(pos, Position_getY(pos) + 1);
			else
			{
				Position_setY(pos, 0);

				fread(&tailleChaine, sizeof(int), 1, fichier);
				chaine = malloc(sizeof(char) * tailleChaine);
				fread(chaine, sizeof(char), tailleChaine, fichier);

				Tutoriel_inserer(tutoriel, plateau, chaine, nbCharParPhrase);
				free(chaine);
			}
		}
		else
			Position_setX(pos, Position_getX(pos) + 1);
	}

	Position_detruire(pos);

	if(ferror(fichier))
	{
		Tutoriel_detruire(tutoriel);
		return NULL;
	}

	return tutoriel;
}

void Tutoriel_inserer(Tutoriel tutoriel, Plateau plateau, char* chaine, int nbCharParPhrase)
{
	int positionChaine = 0, i;
	char* chaine2;

	while(chaine[positionChaine] != '\0')
	{
		Liste_insererCourant(tutoriel->plateaux, plateau);	//On insère le même plateau à chaque fois tant que toute la chaine n'est pas insérée.

		chaine2 = malloc(sizeof(char) * nbCharParPhrase);
		i = positionChaine;

		do
		{
			chaine2[i - positionChaine] = chaine[i];
			i++;
		} while(i < positionChaine + nbCharParPhrase && chaine[i] != '\0');

		if(chaine[i] != ' ' && chaine[i] != '\0')	//On revient au mot entier le plus proche (pour éviter les coupures de mots)
		{
			while(chaine[i] != ' ')
				i--;
			i++;		//On se replace au char suivant
		}

		chaine2[i] = '\0';
		positionChaine = i;

		Liste_insererCourant(tutoriel->chaines, chaine2);

		chaine2 = NULL;
	}
}

Tutoriel Tutoriel_creer()
{
	Tutoriel tutoriel;

	tutoriel = malloc(sizeof(struct Tutoriel));

	tutoriel->chaines = Liste_creer();
	tutoriel->plateaux = Liste_creer();

	return tutoriel;
}

void Tutoriel_detruire(Tutoriel tutoriel)
{
	Plateau plateau;
	char* chaine;

	assert(tutoriel);

	if(Liste_estVide(tutoriel->plateaux))
		return;

	Liste_tete(tutoriel->plateaux);
	Liste_tete(tutoriel->chaines);

	do
	{
		plateau = Liste_courant(tutoriel->plateaux);
		chaine = Liste_courant(tutoriel->chaines);

		assert(plateau);
		assert(chaine);

		Plateau_detruire(plateau);
		free(chaine);

		Liste_supprimerCourant(tutoriel->plateaux);
		Liste_supprimerCourant(tutoriel->chaines);
	} while(!Liste_estVide(tutoriel->plateaux));

	Liste_detruire(tutoriel->plateaux);
	Liste_detruire(tutoriel->chaines);

	free(tutoriel);
}

void Tutoriel_tete(Tutoriel tutoriel)
{
	Liste_tete(tutoriel->plateaux);
	Liste_tete(tutoriel->chaines);
}

int Tutoriel_suivant(Tutoriel tutoriel)
{
	return Liste_suivant(tutoriel->plateaux) && Liste_suivant(tutoriel->chaines);
}

int Tutoriel_precedent(Tutoriel tutoriel)
{
	return Liste_precedent(tutoriel->plateaux) && Liste_precedent(tutoriel->chaines);
}

void Tutoriel_courant(Tutoriel tutoriel, Plateau plateau, char* chaine)
{
	plateau = Liste_courant(tutoriel->plateaux);
	chaine = Liste_courant(tutoriel->chaines);
}
