#ifndef PLATEAU_H_
#define PLATEAU_H_

#include <matrice.h>

#include "Couleur.h"
#include "Position.h"
#include "Chaine.h"

typedef Matrice Plateau;

/**
 * Cr�e un Plateau.
 *
 * @param taille Taille du plateau � cr�er.
 * @return Plateau
 */
Plateau Plateau_creer(int taille);

/**
 * D�truit un Plateau (d�salloue) et place la variable � NULL.
 *
 * @param plateau Pointeur sur plateau.
 */
void Plateau_detruire(Plateau plateau);

/**
 * Renvoie la Couleur de la case (i,j) du plateau.
 *
 * @param plateau
 * @param pos
 * @return Couleur
 */
Couleur Plateau_get(Plateau plateau, Position pos);

/**
 * Met � la case (i,j) du plateau la Couleur pass�e en param�tre.
 *
 * @param plateau
 * @param pos
 * @param couleur
 */
void Plateau_set(Plateau plateau, Position pos, Couleur couleur);

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
 * @return Le plateau copi�. NULL si �a a �chou�.
 */
Plateau Plateau_copier(Plateau from);

/**
 * Sauvegarde dans le fichier pass� en param�tre le plateau.
 *
 * @param plateau
 * @param fichier
 */
void Plateau_sauvegarder(Plateau plateau, FILE* fichier);

/**
 * Charge un plateau � partir d'un fichier pass� en param�tre.
 *
 * @param fichier
 * @return Plateau Le plateau charg�. NULL en cas d'erreur.
 */
Plateau Plateau_charger(FILE* fichier);

/**
 * Produit la chaine � laquelle appartient le pion � la position pos sur le plateau.
 *
 * @param plateau
 * @param pos Position du pion qui appartient � la chaine � d�terminer
 * @return Chaine qui appartient au pion de la position pos. Retourne NULL si la case est VIDE.
 */
Chaine Plateau_determinerChaine(Plateau plateau, Position origine);

/**
 * Realise la capture des pions de la chaine en les enlevant du plateau.
 *
 * @param plateau
 * @param chaine
 */
void Plateau_realiserCapture(Plateau plateau, Chaine chaine);
#endif
