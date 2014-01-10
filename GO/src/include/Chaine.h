/**
 * @file Chaine.h
 * @brief 
 */

#ifndef CHAINE_H_
#define CHAINE_H_

#include "Liste.h"
#include "Pion.h"

typedef Liste Chaine;

/**
 * Cr�e une chaine
 *
 * @return Chaine cr��e.
 */
Chaine Chaine_creer();

/**
 * D�salloue une chaine et met la valeur NULL
 *
 * @param Pointeur sur chaine
 */
void Chaine_detruire(Chaine* chaine);

/**
 * Met la chaine � sa t�te
 * @param chaine
 */
void Chaine_tete(Chaine chaine);

/**
 * Passe � l'�l�ment suivant de la chaine
 * @param chaine
 */
void Chaine_suivant(Chaine chaine);

/**
 * Renvoie un pointeur sur le pion courant de la chaine
 * @param chaine
 * @return Pointeur sur pion
 */
Pion* Chaine_courant(Chaine chaine);

/**
 * Insere un Pointeur sur un Pion dans la chaine
 * @param chaine
 * @param Pointeur sur pion
 */
void Chaine_inserer(Chaine chaine, Pion* pion);

/**
 * Verifie si un pion appartient � la chaine
 * @param chaine
 * @param pion
 * @return 1 si le pion est dans la chaine, sinon 0
 */
int Chaine_appartenir(Chaine chaine, Pion pion);

#endif
