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
	VIDE, 		/**< Pas de données, case vide. */
	BLANC,		/**< Pion blanc. */
	NOIR,  		/**< Pion noir. */
	AURABLANC,	/**< Pion blanc avec une aura autour */
	AURANOIR,	/**< Pion noir avec une aura autour */
	AURAVIDE 	/**< Case vide avec une aura autour */
} Couleur;

/**
 * Retourne le caractère utilisé pour représenter la couleur.
 *
 * @param couleur Couleur à représenter.
 * @return Caractère représentant la couleur.
 */
char Couleur_versChar(Couleur couleur);

#endif
