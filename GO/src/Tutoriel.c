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
	char chaine[512];
	FILE *fichier, *fichier2;
	int n = 0, taille, tailleFichier, i;

	fichier = fopen("assets/Tutoriel.txt", "r");
	fichier2 = fopen("assets/Tutoriel.bin", "wb");

	if(fichier == NULL || fichier2 == NULL)
		return 0;

	fseek(fichier, 0, SEEK_END);
	tailleFichier = ftell(fichier);
	fseek(fichier, 0, SEEK_SET);

	while(ftell(fichier) != tailleFichier)
	{
		if(n % 10 == 9)
		{
			memset(chaine, 0, 512);
			fgets(chaine, 512, fichier);
			taille = strlen(chaine) - 1;
			chaine[taille] = '\0';
			fwrite(&taille, sizeof(int), 1, fichier2);
			fwrite(chaine, sizeof(char), taille, fichier2);
		}
		else
		{
			fgets(chaine, 512, fichier);

			for(i = 0; i < 9; i++)
				chaine[i] = Couleur_charVersCouleur(chaine[i]);

			fwrite(chaine, sizeof(char), 9, fichier2);
		}

		n++;
	}

	fclose(fichier);
	fclose(fichier2);

	return 1;
}

Tutoriel Tutoriel_charger(int nbCharParPhrase)
{
	Tutoriel tutoriel;
	Plateau plateau;
	char* chaine;
	char c;
	FILE* fichier;
	int tailleFichier, tailleChaine, x, y;
	Position pos;

	if((fichier = fopen("assets/Tutoriel.bin", "rb")) == NULL)
		return NULL;

	fseek(fichier, 0, SEEK_END);
	tailleFichier = ftell(fichier);
	fseek(fichier, 0, SEEK_SET);

	tutoriel = Tutoriel_creer();
	plateau = Plateau_creer(9);
	pos = Position_creer(0, 0);

	while(ftell(fichier) != tailleFichier)
	{
		for(y = 0; y < 9; y++)
		{
			for(x = 0; x < 9; x++)
			{
				fread(&c, sizeof(char), 1, fichier);
				Position_setX(pos, x);
				Position_setY(pos, y);
				Plateau_set(plateau, pos, c);
			}
		}

		fread(&tailleChaine, sizeof(int), 1, fichier);
		chaine = malloc(sizeof(char) * (tailleChaine + 1));
		fread(chaine, sizeof(char), tailleChaine, fichier);
		chaine[tailleChaine] = '\0';

		Tutoriel_inserer(tutoriel, plateau, chaine, tailleChaine, nbCharParPhrase);

		free(chaine);
	}

	Plateau_detruire(plateau);
	Position_detruire(pos);

	if(ferror(fichier))
	{
		Tutoriel_detruire(tutoriel);
		return NULL;
	}

	fclose(fichier);

	return tutoriel;
}

void Tutoriel_inserer(Tutoriel tutoriel, Plateau plateau, char* chaine, int tailleChaine, int nbCharParPhrase)
{
	int positionChaine = 0, i;
	char* chaine2;
	Liste sousliste;

	sousliste = Liste_creer();

	Liste_insererCourant(tutoriel->plateaux, Plateau_copier(plateau));

	while(positionChaine < tailleChaine)
	{
		chaine2 = malloc(sizeof(char) * (nbCharParPhrase + 1));
		i = 0;

		while(i < nbCharParPhrase && chaine[positionChaine + i] != '\0')
		{
			chaine2[i] = chaine[positionChaine + i];
			i++;
		}

		if(chaine[positionChaine + i] != ' ' && chaine[positionChaine + i] != '\0')	//On revient au mot entier le plus proche (pour éviter les coupures de mots)
		{
			while(chaine[positionChaine + i] != ' ')
				i--;
			i++;		//On se replace au char suivant
		}

		chaine2[i] = '\0';
		chaine2[nbCharParPhrase] = '\0';

		positionChaine += i;

		Liste_insererCourant(sousliste, chaine2);

		chaine2 = NULL;
	}

	Liste_insererCourant(tutoriel->chaines, sousliste);
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
	Liste sousliste;

	assert(tutoriel);

	if(Liste_estVide(tutoriel->plateaux))
		return;

	Liste_tete(tutoriel->plateaux);
	Liste_tete(tutoriel->chaines);

	do
	{
		plateau = Liste_courant(tutoriel->plateaux);
		sousliste = Liste_courant(tutoriel->chaines);

		assert(plateau);
		assert(sousliste);

		Liste_tete(sousliste);

		do
		{
			chaine = Liste_courant(sousliste);
			free(chaine);
			Liste_supprimerCourant(sousliste);
		} while(!Liste_estVide(sousliste));

		Plateau_detruire(plateau);
		Liste_detruire(sousliste);

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

void Tutoriel_courant(Tutoriel tutoriel, Plateau *plateau, Liste *chaines)
{
	*plateau = Liste_courant(tutoriel->plateaux);
	*chaines = Liste_courant(tutoriel->chaines);
}

int Tutoriel_estPremier(Tutoriel tutoriel)
{
	return Liste_estPremier(tutoriel->plateaux);
}

int Tutoriel_estDernier(Tutoriel tutoriel)
{
	return Liste_estDernier(tutoriel->plateaux);
}
