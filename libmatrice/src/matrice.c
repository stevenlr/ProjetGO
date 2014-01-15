/**
 * @file matrice.c
 * @brief Librairie matrice.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "include/matrice.h"

/**
 *  Matrice de caractères
 */
struct Matrice {
	int nLignes;	/**< Nombre de lignes. */
	int nColonnes;	/**< Nombre de colonnes. */
	char* donnees;	/**< Donnees de la matrice. */
};

Matrice Matrice_creer(int nLignes, int nColonnes, char caractereParDefaut)
{
	Matrice matrice = NULL;

	if(nLignes <= 0 || nColonnes <= 0)
		return NULL;

	matrice = (Matrice) malloc(sizeof(struct Matrice));
	if(matrice == NULL)
		return NULL;

	matrice->nLignes = nLignes;
	matrice->nColonnes = nColonnes;

	matrice->donnees = (char*) malloc(sizeof(char) * nLignes * nColonnes);
	if(matrice->donnees == NULL)
	{
		free(matrice);
		return NULL;
	}

	memset(matrice->donnees, caractereParDefaut, nLignes * nColonnes);

	return matrice;
}

Matrice Matrice_copier(Matrice matrice)
{
	Matrice copie;

	assert(matrice);

	copie = Matrice_creer(matrice->nLignes, matrice->nColonnes, ' ');

	if(copie == NULL)
		return NULL;

	memcpy(copie->donnees, matrice->donnees, matrice->nLignes * matrice->nColonnes * sizeof(char));

	return copie;
}

void Matrice_detruire(Matrice matrice)
{
	assert(matrice != NULL);
	assert(matrice->donnees != NULL);

	free(matrice->donnees);
	free(matrice);
}

void Matrice_afficher(Matrice matrice)
{
	int i, j;

	assert(matrice != NULL);

	for(i = 0; i < matrice->nLignes; i++)
	{
		for(j = 0; j < matrice->nColonnes; j++)
		{
			printf("%c\t", matrice->donnees[j + i * matrice->nColonnes]);
		}

		printf("\n");
	}
}

void Matrice_getTaille(Matrice matrice, int* nLignes, int* nColonnes)
{
	assert(matrice != NULL);

	if(nLignes != NULL)
		*nLignes = matrice->nLignes;

	if(nColonnes != NULL)
		*nColonnes = matrice->nColonnes;
}

char Matrice_get(Matrice matrice, int i, int j)
{
	assert(matrice != NULL);
	assert(i >= 0 && j >= 0 && i < matrice->nLignes && j < matrice->nColonnes);

	return matrice->donnees[j + i * matrice->nColonnes];
}

void Matrice_set(Matrice matrice, int i, int j, char valeur)
{
	assert(matrice != NULL);
	assert(i >= 0 && j >= 0 && i < matrice->nLignes && j < matrice->nColonnes);

	matrice->donnees[j + i * matrice->nColonnes] = valeur;
}
