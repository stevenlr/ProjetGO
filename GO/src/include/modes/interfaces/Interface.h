/**
 * @file Interface.h
 * @brief 
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

/**
 * Une interface est d�finie par deux fonctions : une r�git les entr�es (au clavier pour la console,
 * � la souris ou autres �v�nements en graphique), et une les sorties (l'affichage � l'�cran).
 * Une interface d�pend d'un contexte dont le type lui est propre.
 * Une interface d'entr�e appelle les fonctions �v�nements de l'�cran.
 * Une interface a une fonction d'entr�e et une de sortie pour chaque �cran.
 * Chaque fonctions d"interface prendra en argument les �tats de l'�cran et le contexte de l'interface.
 */

typedef enum {
	GRAPHIQUE,
	CONSOLE
} TypeInterface;

#endif
