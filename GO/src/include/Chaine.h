/**
 * @file Chaine.h
 * @brief 
 */

#ifndef CHAINE_H_
#define CHAINE_H_

#include "Liste.h"
#include "Pion.h"

typedef struct Chaine* Chaine;

/**
 * Cr�e une chaine.
 *
 * @return Chaine cr��e.
 */
Chaine Chaine_creer();

/**
 * D�truit une chaine.
 *
 * @param chaine
 */
void Chaine_detruire(Chaine chaine);

/**
 * D�salloue toutes les positions stock�es.
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
 * V�rifie si une chaine est vide.
 *
 * @param chaine
 * @return 0 si non vide, 1 si vide.
 */
int Chaine_estVide(Chaine chaine);

/**
 * Retourne l'�l�ment courant de la chaine.
 * @param chaine
 * @return Position.
 */
Position Chaine_courant(Chaine chaine);

/**
 * Se place � l'�l�ment suivant de la chaine.
 * @param chaine
 * @return 1 si on a pu s'y placer, 0 si on �tait d�j� � la fin.
 */
int Chaine_suivant(Chaine chaine);

/**
 * Se place � la t�te de la chaine.
 *
 * @param chaine
 */
void Chaine_tete(Chaine chaine);

/**
 * Ins�re une position dans une chaine.
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

#endif
