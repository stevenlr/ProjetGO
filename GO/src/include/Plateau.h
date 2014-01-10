#ifndef PLATEAU_H_
#define PLATEAU_H_

#include <matrice.h>

#include "Couleur.h"

typedef Matrice Plateau;

/**
 * Crée un Plateau.
 *
 * @param taille Taille du plateau à créer.
 * @return Plateau
 */
Plateau Plateau_creer(int taille);

/**
 * Détruit un Plateau (désalloue) et place la variable à NULL.
 *
 * @param plateau Pointeur sur plateau.
 */
void Plateau_detruire(Plateau* plateau);

/**
 * Renvoie la Couleur de la case (i,j) du plateau.
 *
 * @param plateau
 * @param i
 * @param j
 * @return Couleur
 */
Couleur Plateau_get(Plateau plateau, int i, int j);

/**
 * Met à la case (i,j) du plateau la Couleur passée en paramètre.
 *
 * @param plateau
 * @param i
 * @param j
 * @param couleur
 */
void Plateau_set(Plateau plateau, int i, int j, Couleur couleur);

/**
 * Compare deux plateaux
 *
 * @param plateau
 * @param ancienPlateau
 * @return 1 si identique, 0 sinon.
 */
int Plateau_estIdentique(Plateau plateau, Plateau ancienPlateau);

/**
 * Copie le plateau "from" sur le plateau "to"
 *
 * @param from
 * @return Le plateau copié. NULL si ça a échoué.
 */
Plateau Plateau_copier(Plateau from);

/**
 * Sauvegarde dans le fichier passé en paramètre le plateau.
 *
 * @param plateau
 * @param fichier
 */
void Plateau_sauvegarder(Plateau plateau, FILE* fichier);

/**
 * Charge un plateau à partir d'un fichier passé en paramètre.
 *
 * @param fichier
 * @return Plateau Le plateau chargé. NULL en cas d'erreur.
 */
Plateau Plateau_charger(FILE* fichier);

#endif
