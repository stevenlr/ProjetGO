/**
 * @file Contexte.h
 * @brief 
 */

#ifndef CONTEXTE_H_
#define CONTEXTE_H_

/**
 * Un contexte stocke les variables nécessaire aux interfaces.
 * Exemple pour un contexte graphique : la surface window de la SDL.
 */

typedef enum {
	GRAPHIQUE,
	CONSOLE
} TypeContexte;

typedef void* Contexte;

/**
 * Initialise un contexte donné.
 *
 * @param type Type de contexte à créer.
 * @return 0 en cas d'erreur, 1 sinon.
 */
int Contexte_initialiser(TypeContexte type);

/**
 * Détruit le contexte courant.
 */
void Contexte_detruire();

/**
 * Retourne le contexte courant.
 *
 * @return Le contexte courant.
 */
Contexte Contexte_get();

/**
 * Retourne l'id du contexte courant.
 *
 * @return id du contexte.
 */
TypeContexte Contexte_getID();

#endif
