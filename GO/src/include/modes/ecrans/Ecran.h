/**
 * @file Ecran.h
 * @brief 
 */

#ifndef ECRAN_H_
#define ECRAN_H_

/**
 * Un �cran est une partie de l'application, exemple le menu, le guide, et le jeu en lui-m�me.
 * Chaque �cran a son "main" et des fonctions �v�ments. Exemple cliqueCase, debutJeu, ...
 * Ces fonctions g�reront la logique du jeu.
 * Les fonctions �v�nements seront appel�es depuis les interfaces d'entr�e.
 * Elles prendront en entr�e les �tats de l'�cran.
 * Il sera possible de changer d'�cran : � la fin de la boucle principale de chaque �cran,
 * une v�rification sur le changement d'�cran sera effectu�e.
 * L'application se comporte comme une machine � �tats :
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
