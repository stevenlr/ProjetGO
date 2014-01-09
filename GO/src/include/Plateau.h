#ifndef PLATEAU_H_
#define PLATEAU_H_

#include "Couleur.h"

typedef Matrice* Plateau;

/**
 * Cr�er un Plateau
 *
 * @param taille du plateau � cr�er
 * @return Plateau
 */

Plateau Plateau_creer(int taille);

/**
 * D�truit un Plateau (d�salloue) et la variable a NULL
 *
 * @param Pointeur sur plateau
 */

void Plateau_detruire(Plateau* plateau);

/**
 * Renvoie la Couleur de la case (i,j) du plateau
 *
 * @param plateau
 * @param i
 * @param j
 * @return Couleur
 */

Couleur Plateau_get(Plateau plateau, int i, int j);

/**
 * Met � la case (i,j) du plateau la Couleur pass�e en param�tre
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
 * @param to
 * @return Retourne 0 en de tailles diff�rentes, sinon 1.
 */

int Plateau_copier(Plateau from, Plateau to);

/**
 * Sauvegarde dans le fichier pass� en param�tre le plateau.
 *
 * @param plateau
 * @param fichier
 */

void Plateau_sauvegarder(Plateau plateau,FILE* fichier);

/**
 * Charge un plateau � partir d'un fichier pass� en param�tre.
 *
 * @param fichier
 * @return Plateau
 */

Plateau Plateau_charger(FILE* fichier);

#endif
