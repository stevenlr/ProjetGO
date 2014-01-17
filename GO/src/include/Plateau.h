#ifndef PLATEAU_H_
#define PLATEAU_H_

#include <stdio.h>
#include <matrice.h>

#include "Couleur.h"
#include "Position.h"
#include "Chaine.h"
#include "Chaines.h"

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
 * Renvoie la taille du plateau.
 *
 * @param plateau
 * @return Taille du plateau.
 */
int Plateau_getTaille(Plateau plateau);

/**
 * Met à la case (i,j) du plateau la Couleur passée en paramètre.
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

/**
 * Produit la chaine à laquelle appartient le pion à la position pos sur le plateau.
 *
 * @param plateau
 * @param pos Position du pion qui appartient à la chaine à déterminer
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

/**
 * Détermine les chaînes éventuellement capturées par la pose du pion.
 * Valide est mis à 1 si le coup était valide, 0 sinon.
 *
 * @param plateau
 * @param pion
 * @param valide
 * @return Les chaînes éventuellement capturées.
 */
Chaines Plateau_capturerChaines(Plateau plateau, Pion pion, int* valide);

/**
 * Determine la position des yeux relatifs à une chaine.
 *
 * @return NULL si aucun oeil, sinon la liste des positions des yeux
 */
Positions Plateau_determinerYeux(Plateau plateau, Chaine chaine);

/**
 * Calcule le score de la partie.
 *
 * @param plateau
 * @param komi
 * @param scoreNoir
 * @param scoreBlanc
 */
void Plateau_calculerScore(Plateau plateau, int komi, int* scoreNoir, int* scoreBlanc);

#endif
