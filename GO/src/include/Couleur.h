/**
 * @file Couleur.h
 * @brief En-t�te de gestion des couleurs de pions.
 */

#ifndef COULEUR_H_
#define COULEUR_H_

/**
 * Couleur d'un pion.
 */
typedef enum {
	VIDE, 	/**< Pas de donn�es, case vide. */
	BLANC,	/**< Pion blanc. */
	NOIR  	/**< Pion noir. */
} Couleur;

/**
 * Retourne le caract�re utilis� pour repr�senter la couleur.
 *
 * @param couleur Couleur � repr�senter.
 * @return Caract�re repr�sentant la couleur.
 */
char Couleur_versChar(Couleur couleur);

#endif
