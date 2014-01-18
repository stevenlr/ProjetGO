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
 * Guide  ---> Menu  ----> Options de partie ---> Jeu
 *       <---       <---------------------------
 *
 * Nommage des fonctions :
 * Ecran{Type}_main();
 * Ecran{Type}_evenement{NomDeLEvenement}(...);
 */

typedef void (*FonctionEntreeEcran)(void*);
typedef void (*FonctionMainEcran)(void);
typedef void (*FonctionSortieEcran)(void*);

typedef enum {
	NONE,
	MENU,
	OPTIONS,
	JEU,
	GUIDE
} TypeEcran;

/**
 * Retourne l'ID de l'�cran courant.
 *
 * @return id de l'�cran courant.
 */
TypeEcran Ecran_getID();

/**
 * Retourne l'ID de l'�cran suivant.
 *
 * @return id de l'�cran suivant.
 */
TypeEcran Ecran_getIDProchain();

/**
 * Change d'�cran courant.
 *
 * @param type ID �cran.
 */
void Ecran_setIDProchain(TypeEcran type);

/**
 * V�rifie si on doit changer d'�cran.
 *
 * @return 1 si on doit changer, 0 sinon.
 */
int Ecran_doitChanger();

/**
 * Change l'�cran courant si besoin.
 */
void Ecran_changer();

/**
 * Retourne la fonction main de l'�cran courant.
 *
 * @return Fonction main de l'�cran.
 */
FonctionMainEcran Ecran_getFonctionMain();

#endif
