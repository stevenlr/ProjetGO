/**
 * @file matrice.h
 * @brief En-t�tes de la librairie matrice
 */

#ifndef MATRICE_H_
#define MATRICE_H_

/**
 *  Matrice de caract�res
 */
typedef struct {
	int nLignes;	/**< Nombre de lignes. */
	int nColonnes;	/**< Nombre de colonnes. */
	char* donnees;	/**< Donnees de la matrice. */
} Matrice;

/**
 * Alloue une matrice.
 *
 * @param nLignes Nombre de lignes de la matrice.
 * @param nColonnes Nombre de colonnes de la matrice.
 * @param caractereParDefaut Caract�re avec lequel remplir toute la matrice.
 * @return Matrice allou�e. NULL si la matrice n'a pas pu �tre allou�e.
 */
Matrice* Matrice_allouer(int nLignes, int nColonnes, char caractereParDefaut);

/**
 * D�truit une matrice.
 *
 * @param matrice Matrice � d�truire.
 */
void Matrice_detruire(Matrice* matrice);

/**
 * Affiche une matrice.
 *
 * @param matrice Matrice � afficher.
 */
void Matrice_afficher(Matrice* matrice);

/**
 * R�cup�re la taille d'une matrice.
 * Si un des pointeurs r�cup�rant la taille est � NULL,
 * celui-ci n'est pas trait�.
 *
 * @param matrice Matrice dont il faut r�cup�rer la taille.
 * @param nLignes Nombre de lignes.
 * @param nColonnes Nombre de colonnes.
 */
void Matrice_getTaille(Matrice* matrice, int* nLignes, int* nColonnes);

/**
 * R�cup�re la valeur d'un coefficient de la matrice.
 *
 * @param matrice Matrice � traiter.
 * @param i Ligne du coefficient.
 * @param j Colonne du coefficient.
 * @return Le coefficient.
 */
char Matrice_get(Matrice* matrice, int i, int j);

/**
 * Assigne une valeur � un coefficient de la matrice.
 *
 * @param matrice Matrice � traiter.
 * @param i Ligne du coefficient.
 * @param j Colonne du coefficient.
 * @param valeur Valeur � assigner.
 */
void Matrice_set(Matrice* matrice, int i, int j, char valeur);

#endif
