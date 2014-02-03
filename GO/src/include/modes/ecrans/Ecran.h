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
 * Guide  ---> Menu  ----> Options de partie ---> Jeu
 *       <---       <---------------------------
 *
 * Nommage des fonctions :
 * Ecran{Type}_main();
 * Ecran{Type}_evenement{NomDeLEvenement}(...);
 */

/**
 * Fonction d'un écran gérant les entrées.
 */
typedef void (*FonctionEntreeEcran)(void*);

/**
 * Fonctions d'un écran gérant la logique.
 */
typedef void (*FonctionMainEcran)(void);

/**
 * Fonctions d'un écran gérant les sorties.
 * @param
 */
typedef void (*FonctionSortieEcran)(void*);

/**
 * Les différents écrans du jeu.
 */
typedef enum {
	NONE,   //!< NONE
	MENU,   //!< MENU
	OPTIONS,//!< OPTIONS
	JEU,    //!< JEU
	GUIDE   //!< GUIDE
} TypeEcran;

/**
 * Retourne l'ID de l'écran courant.
 *
 * @return id de l'écran courant.
 */
TypeEcran Ecran_getID();

/**
 * Retourne l'ID de l'écran suivant.
 *
 * @return id de l'écran suivant.
 */
TypeEcran Ecran_getIDProchain();

/**
 * Change d'écran courant.
 *
 * @param type ID écran.
 */
void Ecran_setIDProchain(TypeEcran type);

/**
 * Vérifie si on doit changer d'écran.
 *
 * @return 1 si on doit changer, 0 sinon.
 */
int Ecran_doitChanger();

/**
 * Change l'écran courant si besoin.
 */
void Ecran_changer();

/**
 * Retourne la fonction main de l'écran courant.
 *
 * @return Fonction main de l'écran.
 */
FonctionMainEcran Ecran_getFonctionMain();

#endif
