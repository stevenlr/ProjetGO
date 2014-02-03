/**
 * @file EtatsMenu.h
 * @brief 
 */

#ifndef ETATSMENU_H_
#define ETATSMENU_H_

/**
 * Etats de l'écran de menu.
 */
typedef struct {
	int continuer;		//!< 1 tant qu'on doit continuer sur cet écran.
	int premiereBoucle;	//!< 1 si c'est la première boucle de la logique de l'écran.
	int derniereBoucle;	//!< 1 si c'est la dernière boucle avant fermeture de l'écran.
} EtatsMenu;

#endif
