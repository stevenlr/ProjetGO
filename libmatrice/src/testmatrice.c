/**
 * @file testmatrice.c
 * @brief Tests de la librairie matrice.
 */

#include <stdio.h>
#include <stdlib.h>

#include "include/matrice.h"

int main(int argc, char* argv[])
{
	int w;
	Matrice* matrice = Matrice_allouer(3, 4, '.');

	Matrice_afficher(matrice);

	Matrice_getTaille(matrice, NULL, &w);
	printf("%d colonnes.\n", w);

	printf("Valeur en 2, 1 : %c\n", Matrice_get(matrice, 2, 1));

	Matrice_set(matrice, 2, 1, 'O');
	Matrice_afficher(matrice);

	Matrice_detruire(matrice);

	return 0;
}
