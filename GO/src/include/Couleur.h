/**
 * @file Couleur.h
 * @brief En-tête de gestion des couleurs de pions.
 */

#ifndef COULEUR_H_
#define COULEUR_H_

/**
 * Couleur d'un pion.
 */
typedef enum {
	VIDE, 	/**< Pas de données, case vide. */
	BLANC,	/**< Pion blanc. */
	NOIR  	/**< Pion noir. */
} Couleur;

/**
 * Retourne le caractère utilisé pour représenter la couleur.
 *
 * @param couleur Couleur à représenter.
 * @return Caractère représentant la couleur.
 */
char Couleur_versChar(Couleur couleur);

#endif
