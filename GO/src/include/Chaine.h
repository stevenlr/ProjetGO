/**
* @file Chaine.h
* @brief
*/

#ifndef CHAINE_H_
#define CHAINE_H_

#include "Liste.h"
#include "Pion.h"
#include "Positions.h"
#include "Plateau.h"
#include "Libertes.h"

typedef struct Chaine* Chaine;

/**
 * Crée une chaine.
 *
 * @return Chaine créée.
 */
Chaine Chaine_creer();

/**
 * Détruit une chaine.
 *
 * @param chaine
 */
void Chaine_detruire(Chaine chaine);

/**
 * Désalloue toutes les positions stockées.
 *
 * @param chaine
 */
void Chaine_vider(Chaine chaine);

/**
 * Verifie si un pion appartient à la chaine
 * @param chaine
 * @param pion
 * @return 1 si le pion est dans la chaine, sinon 0
 */
int Chaine_appartient(Chaine chaine, Position position);

/**
 * Vérifie si une chaine est vide.
 *
 * @param chaine
 * @return 0 si non vide, 1 si vide.
 */
int Chaine_estVide(Chaine chaine);

/**
 * Retourne l'élément courant de la chaine.
 * @param chaine
 * @return Position.
 */
Position Chaine_courant(Chaine chaine);

/**
 * Se place à l'élément suivant de la chaine.
 * @param chaine
 * @return 1 si on a pu s'y placer, 0 si on était à la fin.
 */
int Chaine_suivant(Chaine chaine);

/**
 * Se place à la tête de la chaine.
 *
 * @param chaine
 */
void Chaine_tete(Chaine chaine);

/**
 * Insère une position dans une chaine.
 *
 * @param chaine
 * @param position
 */
void Chaine_inserer(Chaine chaine, Position position);

/**
 * Inserer la Couleur couleur à la chaine;
 *
 * @param chaine
 * @param couleur
 */
void Chaine_setCouleur(Chaine chaine, Couleur couleur);

/**
 * Renvoie la couleur de la chaine
 *
 * @param chaine
 * @return couleur
 */
Couleur Chaine_getCouleur(Chaine chaine);

/**
 * Determine la position des yeux relatifs à une chaine.
 *
 * @return NULL si aucun oeil, sinon la liste des positions des yeux
 */
Positions Chaine_determinerYeux(Plateau plateau, Chaine chaine);

#endif
