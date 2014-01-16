/**
 * @file Ecran.h
 * @brief 
 */

#ifndef ECRAN_H_
#define ECRAN_H_

/**
 * Un écran est une partie de l'application, exemple le menu, le guide, et le jeu en lui-même.
 * Chaque écran a son "main" et des fonctions évéments. Exemple cliqueCase, debutJeu, ...
 * Ces fonctions gèreront la logique du jeu.
 * Les fonctions événements seront appelées depuis les interfaces d'entrée.
 * Elles prendront en entrée les états de l'écran.
 * Il sera possible de changer d'écran : à la fin de la boucle principale de chaque écran,
 * une vérification sur le changement d'écran sera effectuée.
 * L'application se comporte comme une machine à états :
 *
 * Guide  ---> Menu  ---> Jeu
 *       <---       <---
 *
 * Nommage des fonctions :
 * Ecran{Type}_main(Contexte contexte);
 * Ecran{Type}_evenement{NomDeLEvenement}(Etats{Type} etats);
 */

typedef enum {
	MENU,
	JEU,
	GUIDE
} TypeEcran;

#endif
