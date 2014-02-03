/**
 * @file EtatsMenu.h
 * @brief 
 */

#ifndef ETATSMENU_H_
#define ETATSMENU_H_

/**
 * Etats de l'�cran de menu.
 */
typedef struct {
	int continuer;		//!< 1 tant qu'on doit continuer sur cet �cran.
	int premiereBoucle;	//!< 1 si c'est la premi�re boucle de la logique de l'�cran.
	int derniereBoucle;	//!< 1 si c'est la derni�re boucle avant fermeture de l'�cran.
} EtatsMenu;

#endif
