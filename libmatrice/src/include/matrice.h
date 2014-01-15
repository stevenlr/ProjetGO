/**
 * @file matrice.h
 * @brief En-têtes de la librairie matrice
 */

#ifndef MATRICE_H_
#define MATRICE_H_

typedef struct Matrice* Matrice;

/**
 * Alloue une matrice.
 *
 * @param nLignes Nombre de lignes de la matrice.
 * @param nColonnes Nombre de colonnes de la matrice.
 * @param caractereParDefaut Caractère avec lequel remplir toute la matrice.
 * @return Matrice allouée. NULL si la matrice n'a pas pu être allouée.
 */
Matrice Matrice_creer(int nLignes, int nColonnes, char caractereParDefaut);

/**
 * Copie une matrice.
 *
 * @param matrice Matrice à copier.
 * @return Matrice copiée.
 */
Matrice Matrice_copier(Matrice matrice);

/**
 * Détruit une matrice.
 *
 * @param matrice Matrice à détruire.
 */
void Matrice_detruire(Matrice matrice);

/**
 * Affiche une matrice.
 *
 * @param matrice Matrice à afficher.
 */
void Matrice_afficher(Matrice matrice);

/**
 * Récupère la taille d'une matrice.
 * Si un des pointeurs récupérant la taille est à NULL,
 * celui-ci n'est pas traité.
 *
 * @param matrice Matrice dont il faut récupérer la taille.
 * @param nLignes Nombre de lignes.
 * @param nColonnes Nombre de colonnes.
 */
void Matrice_getTaille(Matrice matrice, int* nLignes, int* nColonnes);

/**
 * Récupère la valeur d'un coefficient de la matrice.
 *
 * @param matrice Matrice à traiter.
 * @param i Ligne du coefficient.
 * @param j Colonne du coefficient.
 * @return Le coefficient.
 */
char Matrice_get(Matrice matrice, int i, int j);

/**
 * Assigne une valeur à un coefficient de la matrice.
 *
 * @param matrice Matrice à traiter.
 * @param i Ligne du coefficient.
 * @param j Colonne du coefficient.
 * @param valeur Valeur à assigner.
 */
void Matrice_set(Matrice matrice, int i, int j, char valeur);

#endif
