/**
 * @file Interface.h
 * @brief 
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

/**
 * Une interface est définie par deux fonctions : une régit les entrées (au clavier pour la console,
 * à la souris ou autres événements en graphique), et une les sorties (l'affichage à l'écran).
 * Une interface dépend d'un contexte dont le type lui est propre.
 * Une interface d'entrée appelle les fonctions événements de l'écran.
 * Une interface a une fonction d'entrée et une de sortie pour chaque écran.
 * Chaque fonctions d"interface prendra en argument les états de l'écran et le contexte de l'interface.
 */

typedef enum {
	GRAPHIQUE,
	CONSOLE
} TypeInterface;

#endif
